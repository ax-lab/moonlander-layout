#include "moonlander.h"
#include "version.h"

#define DOUBLE_TAP_DEBOUNCE_MS 50
float double_tap_audio_cue[][2] = SONG(H__NOTE(_A2));

#ifdef CONSOLE_ENABLE
	#define ENABLE_OUTPUT 1
#else
	#define ENABLE_OUTPUT 0
#endif

#if ENABLE_OUTPUT
	#include "print.h"
	#define output uprintf
#else
	#define output(...) (void)0
#endif

#include "utilities.h"

#include "leds.h"
#include "overlay.h"

#include "overlay_pong.h"
#include "overlay_rainbow.h"
#include "overlay_simple_snake.h"
#include "overlay_menu.h"

#include "layer_keys.h"
#include "layer_map.h"
#include "layer_leds.h"
#include "layer_dance.h"

extern bool g_suspend_state;
extern rgb_config_t rgb_matrix_config;

static uint32_t welcome_msg_timer = 0;
static bool welcome_msg_trigger = true;

void keyboard_post_init_user(void)
{
	rgb_matrix_enable();
	welcome_msg_timer = timer_read32();
	welcome_msg_trigger = false;
}

void matrix_scan_user(void)
{
	if (!welcome_msg_trigger) {
		if (timer_elapsed32(welcome_msg_timer) > 5000) {
			output("keyboard init: %dx%d (%d leds)", MATRIX_ROWS, MATRIX_COLS, DRIVER_LED_TOTAL);
			welcome_msg_trigger = true;
		}
	}
}

void set_layer_color(int layer)
{
	static HSV ncl = NCL;

	if (layer < 0 || layer >= LAYER_MAX_COUNT) {
		return;
	}

	for (int i = 0; i < DRIVER_LED_TOTAL; i++)
	{
		for (int cur = layer; cur >= 0; cur--) {
			HSV hsv = {
				.h = pgm_read_byte(&ledmap[cur][i][0]),
				.s = pgm_read_byte(&ledmap[cur][i][1]),
				.v = pgm_read_byte(&ledmap[cur][i][2]),
			};

			if (cur > 0 && (!layer_state_is(cur) || (hsv.h == ncl.h && hsv.s == ncl.s && hsv.v == ncl.v))) {
				continue;
			}

			if (!hsv.h && !hsv.s && !hsv.v)
			{
				rgb_matrix_set_color(i, 0, 0, 0);
			}
			else
			{
				RGB rgb = hsv_to_rgb(hsv);
				float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
				rgb_matrix_set_color(i, f * rgb.r, f * rgb.g, f * rgb.b);
			}
			break;
		}
	}
}

// Defined at moonlander.c
extern bool is_launching;
extern bool mcp23018_leds[3];

void rgb_matrix_indicators_user(void)
{
	if (!is_launching) {
		led_t led_state = host_keyboard_led_state();
		uint8_t cur_layer = biton32(layer_state);
		bool alert_numlock = !led_state.num_lock && (cur_layer == LAYER_PAD || cur_layer == LAYER_G_MOD);
		ML_LED_5(alert_numlock);
		ML_LED_6(led_state.caps_lock);
	}

	if (g_suspend_state || keyboard_config.disable_layer_led)
	{
		return;
	}

	if (current_overlay.rgb != NULL) {
		current_overlay.rgb();
		return;
	}

	set_layer_color(biton32(layer_state));
}

typedef struct {
	uint16_t keycode;
	uint16_t prev_keycode;

	uint32_t time;
	uint32_t prev_time;

	uint32_t press_time;
	uint32_t prev_press_time;
} special_key_state_t;

bool process_special_key(special_key_state_t *state, keyrecord_t *record);

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
	static bool is_menu_pressed = false;

	static special_key_state_t state = { 0 };

	bool pressed = record->event.pressed;

	state.prev_keycode = state.keycode;
	state.keycode = keycode;

	state.prev_time = state.time;
	state.time = timer_read32();

	if (pressed) {
		state.prev_press_time = state.press_time;
		state.press_time = state.time;
	}

	if (keycode == KC_LGUI) {
		is_menu_pressed = record->event.pressed;
	}

	output("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n",
		keycode, record->event.key.col, record->event.key.row, record->event.pressed,
		record->event.time, record->tap.interrupted, record->tap.count);

	if (current_overlay.process != NULL) {
		if (!record->event.pressed && current_overlay_skip_not_pressed) {
			current_overlay_skip_not_pressed = false;
			return false;
		} else {
			current_overlay_skip_not_pressed = false;
		}
		return current_overlay.process(keycode, record);
	}

	if (record->event.key.col == 6 && record->event.key.row == 0 && is_menu_pressed) {
		unregister_code(KC_LGUI);
		if (!record->event.pressed) {
			open_menu();
		}
		return false;
	}

	if (process_special_key(&state, record)) {
		return false;
	}

	switch (keycode)
	{
		case RGB_SLD:
			if (pressed)
			{
				rgblight_mode(1);
			}
			return false;
	}

	return true;
}

bool process_special_key(special_key_state_t *state, keyrecord_t *record)
{
	static bool s_ctrl   = false;
	static bool s_shift  = false;
	static bool s_symbol = false;

	static bool accents = false;

	static bool s_ctrl_alt  = false;
	static bool s_shift_alt = false;

	// we need to keep track of the normal (non-special) modifier keys so
	// that we don't cancel a pressed modifier from the mods layer
	static bool l_ctrl  = false;
	static bool l_shift = false;
	static bool l_alt   = false;

	bool pressed = record->event.pressed;

	/*
		For a double press to be considered the key must be pressed twice
		in sequence (with no keys in-between) and the timing must be:

			[==============]                [====/ ... /====]
			<----- TT -----><----- TT ----->

		Where TT must be less or equal to the tapping term.
	*/
	uint32_t delta = state->time - state->prev_time;
	bool is_double_press = pressed &&
		(state->keycode == state->prev_keycode) &&
		(delta <= TAPPING_TERM && delta >= DOUBLE_TAP_DEBOUNCE_MS) &&
		(state->time - state->prev_press_time <= 2 * TAPPING_TERM);

	// Double pressing CTRL and SHIFT enables the ALT key.
	bool alt_pressed = get_mods() & MOD_MASK_ALT;
	bool can_enable_alt = pressed && is_double_press && !alt_pressed;

	bool is_double_press_key = false;
	switch (state->keycode) {
		case KC_LCTRL:
			l_ctrl = pressed;
			break;
		case KC_LSHIFT:
			l_shift = pressed;
			break;
		case KC_LALT:
			l_alt = pressed;
			break;
		case S_CTRL:
			s_ctrl = pressed;
			s_ctrl_alt = is_double_press_key = can_enable_alt;
			break;
		case S_SHIFT:
			s_shift = pressed;
			s_shift_alt = is_double_press_key = can_enable_alt;
			break;
		case S_SYMBOL:
			if (is_double_press) {
				s_symbol = false;
				accents = true;
			} else {
				s_symbol = pressed;
				accents = false;
			}
			break;
		default:
			return false;
	}

	if (is_double_press_key) {
		PLAY_SONG(double_tap_audio_cue);
	}

	bool enable_shift = l_shift || (s_shift && (!s_symbol || s_shift_alt));
	bool enable_ctrl = l_ctrl || s_ctrl;
	bool enable_alt = l_alt || s_ctrl_alt || s_shift_alt;

	if (enable_shift) {
		add_key(KC_LSHIFT);
		add_mods(MOD_LSFT);
	} else {
		del_key(KC_LSHIFT);
		del_mods(MOD_LSFT);
	}

	if (enable_ctrl) {
		add_key(KC_LCTRL);
		add_mods(MOD_LCTL);
	} else {
		del_key(KC_LCTRL);
		del_mods(MOD_LCTL);
	}

	if (enable_alt) {
		add_key(KC_LALT);
		add_mods(MOD_LALT);
	} else {
		del_key(KC_LALT);
		del_mods(MOD_LALT);
	}

	if (s_symbol && (s_shift && !s_shift_alt)) {
		layer_on(LAYER_MODS);
		layer_off(LAYER_SYM);
		layer_off(LAYER_ACC);
	} else if (s_symbol) {
		layer_on(LAYER_SYM);
		layer_off(LAYER_MODS);
		layer_off(LAYER_ACC);
	} else if (accents) {
		layer_on(LAYER_ACC);
		layer_off(LAYER_SYM);
		layer_off(LAYER_MODS);
	} else {
		layer_off(LAYER_SYM);
		layer_off(LAYER_MODS);
		layer_off(LAYER_ACC);
	}

	send_keyboard_report();
	return true;
}
