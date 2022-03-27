#include "moonlander.h"
#include "version.h"

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

#include "util.h"

#include "leds.h"
#include "overlay.h"

#include "overlay_pong.h"
#include "overlay_rainbow.h"
#include "overlay_simple_snake.h"
#include "overlay_menu.h"

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)
#define ES_LESS_MAC KC_GRAVE
#define ES_GRTR_MAC LSFT(KC_GRAVE)
#define ES_BSLS_MAC ALGR(KC_6)
#define NO_PIPE_ALT KC_GRAVE
#define NO_BSLS_ALT KC_EQUAL
#define LSA_T(kc) MT(MOD_LSFT | MOD_LALT, kc)
#define BP_NDSH_MAC ALGR(KC_8)
#define SE_SECT_MAC ALGR(KC_6)
#define MOON_LED_LEVEL LED_LEVEL

enum custom_keycodes
{
	RGB_SLD = ML_SAFE_RANGE,
};

enum tap_dance_codes
{
	DANCE_0,
	DANCE_1,
	DANCE_2,
	DANCE_3,
	DANCE_4,
	DANCE_5,
	DANCE_6,
	DANCE_7,
	DANCE_8,
	DANCE_9,
	DANCE_10,
	DANCE_11,
	DANCE_12,
	DANCE_13,
	DANCE_14,
	DANCE_15,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_moonlander(
		TD(DANCE_0), KC_1, KC_2, KC_3, KC_4, KC_5, MO(8), MO(8), KC_6, KC_7, KC_8, KC_9, KC_0, KC_UP,
		TT(12), KC_Q, KC_W, KC_E, KC_R, KC_T, TG(14), TG(14), KC_Y, KC_U, KC_I, KC_O, KC_UNDS, KC_DOWN,
		KC_BSPACE, KC_A, KC_S, KC_D, KC_F, KC_G, KC_DELETE, KC_ESCAPE, KC_H, KC_J, KC_K, KC_L, KC_P, MO(9),
		KC_LCTRL, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, KC_QUOTE, TD(DANCE_1),
		KC_LGUI, KC_LALT, MO(8), MO(7), KC_LSHIFT, MO(4), MO(4), MO(5), MO(6), KC_LEFT, KC_RIGHT, TG(13),
		KC_ENTER, KC_TAB, KC_SPACE, KC_ENTER, LSFT(KC_TAB), KC_SPACE),
	[1] = LAYOUT_moonlander(
		KC_ESCAPE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_PAUSE, KC_TRANSPARENT, KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRANSPARENT,
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_DELETE, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_UP, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_LSHIFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_BSPACE, KC_TRANSPARENT, KC_TRANSPARENT, KC_LEFT, KC_DOWN, KC_RIGHT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_LCTRL, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_GRAVE, KC_LALT, KC_TRANSPARENT, MO(10), KC_SPACE, KC_ENTER, TO(2), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		MO(11), KC_CAPSLOCK, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT),
	[2] = LAYOUT_moonlander(
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, TO(1), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT),
	[3] = LAYOUT_moonlander(
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_Q, KC_W, KC_F, KC_P, KC_B, KC_TRANSPARENT, KC_TRANSPARENT, KC_J, KC_L, KC_U, KC_Y, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_A, KC_R, KC_S, KC_T, KC_G, KC_TRANSPARENT, KC_TRANSPARENT, KC_M, KC_N, KC_E, KC_I, KC_O, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_Z, KC_X, KC_C, KC_D, KC_V, KC_K, KC_H, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, TD(DANCE_2), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT),
	[4] = LAYOUT_moonlander(
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, TD(DANCE_3), TD(DANCE_4), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_LSHIFT, KC_LGUI, KC_LALT, KC_LCTRL, KC_TRANSPARENT, LALT(KC_TAB), LALT(KC_TAB), KC_TRANSPARENT, KC_RCTRL, KC_RALT, KC_RGUI, KC_RSHIFT, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_AUDIO_VOL_UP, KC_AUDIO_VOL_DOWN, KC_AUDIO_MUTE, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT),
	[5] = LAYOUT_moonlander(
		KC_TRANSPARENT, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_TRANSPARENT, KC_TRANSPARENT, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
		KC_TRANSPARENT, KC_CIRC, KC_LABK, KC_AMPR, KC_RABK, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_SLASH, KC_BSLASH, KC_ASTR, KC_PERC, KC_F12,
		KC_TRANSPARENT, KC_GRAVE, KC_COLN, KC_EQUAL, KC_MINUS, KC_PLUS, LGUI(KC_KP_2), LGUI(KC_KP_1), KC_LBRACKET, KC_LPRN, KC_LCBR, KC_QUES, KC_SCOLON, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_DLR, KC_PIPE, KC_DQUO, KC_EXLM, KC_TILD, KC_RBRACKET, KC_RPRN, KC_RCBR, KC_AT, KC_HASH, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_F22, KC_F20, KC_F21, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, DYN_MACRO_PLAY1, DYN_MACRO_PLAY2, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT),
	[6] = LAYOUT_moonlander(
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_NUMLOCK, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_SCROLLLOCK, KC_TRANSPARENT, KC_TRANSPARENT, KC_SLASH, KC_TRANSPARENT, KC_ASTR, KC_PERC, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_1, KC_2, KC_3, KC_4, KC_5, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_7, KC_8, KC_9, KC_0, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_DLR, KC_TRANSPARENT, KC_MINUS, KC_EQUAL, KC_TRANSPARENT, KC_TRANSPARENT, KC_6, KC_TRANSPARENT, KC_TRANSPARENT, KC_HASH, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_RALT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT),
	[7] = LAYOUT_moonlander(
		RCTL(RSFT(KC_UP)), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		LGUI(LSFT(KC_LEFT)), LGUI(LSFT(KC_RIGHT)), KC_PGUP, KC_UP, KC_F12, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, KC_MEDIA_PREV_TRACK, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_LCTRL, KC_LALT, KC_LGUI, KC_LSHIFT, KC_TRANSPARENT,
		LALT(KC_TAB), KC_TRANSPARENT, KC_PGDOWN, KC_MINUS, KC_EQUAL, KC_TRANSPARENT, KC_TRANSPARENT, LGUI(LSFT(KC_LEFT)), LGUI(LSFT(KC_RIGHT)), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		LGUI(KC_TAB), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_LSHIFT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT),
	[8] = LAYOUT_moonlander(
		KC_PAUSE, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F11, KC_TRANSPARENT, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
		KC_TRANSPARENT, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F12, KC_TRANSPARENT, KC_F12, KC_F7, KC_F8, KC_F9, KC_F15, KC_F12,
		KC_TRANSPARENT, KC_LSHIFT, KC_LGUI, KC_LALT, KC_LCTRL, KC_TRANSPARENT, KC_INSERT, KC_APPLICATION, KC_F11, KC_F4, KC_F5, KC_F6, KC_F14, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_F10, KC_F1, KC_F2, KC_F3, KC_F13, KC_TRANSPARENT,
		KC_CAPSLOCK, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT),
	[9] = LAYOUT_moonlander(
		KC_TRANSPARENT, RALT(KC_A), KC_TRANSPARENT, KC_TRANSPARENT, RALT(KC_F), RALT(KC_J), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, RALT(KC_N), KC_TRANSPARENT, RALT(KC_S), KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, RALT(KC_B), RALT(KC_Z), KC_TRANSPARENT, RALT(KC_G), RALT(KC_K), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, RALT(KC_O), KC_TRANSPARENT, RALT(KC_T), KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, RALT(KC_C), RALT(KC_E), RALT(KC_W), RALT(KC_H), RALT(KC_L), KC_TRANSPARENT, KC_TRANSPARENT, RALT(KC_X), RALT(KC_P), RALT(KC_R), RALT(KC_U), KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, RALT(KC_D), RALT(KC_0), RALT(KC_Y), RALT(KC_I), RALT(KC_M), KC_TRANSPARENT, RALT(KC_Q), KC_TRANSPARENT, RALT(KC_V), KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT),
	[10] = LAYOUT_moonlander(
		TO(0), KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_TRANSPARENT, KC_TRANSPARENT, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
		KC_TRANSPARENT, KC_7, KC_8, KC_9, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_F12,
		KC_0, KC_4, KC_5, KC_6, KC_EQUAL, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_1, KC_2, KC_3, KC_MINUS, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT),
	[11] = LAYOUT_moonlander(
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_F12, KC_F7, KC_F8, KC_F9, KC_TRANSPARENT, KC_UP, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_F11, KC_F4, KC_F5, KC_F6, KC_LEFT, KC_RIGHT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_F10, KC_F1, KC_F2, KC_F3, KC_TRANSPARENT, KC_DOWN, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT),
	[12] = LAYOUT_moonlander(
		LCTL(KC_W), KC_1, KC_2, KC_3, LALT(KC_F4), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		TO(0), KC_4, KC_5, KC_6, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_7, KC_8, KC_9, KC_UP, KC_TRANSPARENT, TD(DANCE_5), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		OSM(MOD_LCTL), KC_TRANSPARENT, KC_TRANSPARENT, KC_LEFT, KC_DOWN, KC_RIGHT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		OSM(MOD_LGUI), OSM(MOD_LALT), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, TO(1), TO(3), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT),
	[13] = LAYOUT_moonlander(
		TD(DANCE_6), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, LALT(KC_F4), KC_TRANSPARENT, KC_TRANSPARENT, TO(0), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, WEBUSB_PAIR, RESET,
		KC_TRANSPARENT, KC_TRANSPARENT, LCTL(KC_W), LCTL(KC_PGUP), LCTL(KC_PGDOWN), KC_TRANSPARENT, KC_TRANSPARENT, DYN_MACRO_PLAY1, DYN_REC_START1, DYN_REC_STOP, KC_TRANSPARENT, KC_TRANSPARENT, TOGGLE_LAYER_COLOR, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, TD(DANCE_7), DYN_MACRO_PLAY2, DYN_REC_START2, DYN_REC_STOP, KC_TRANSPARENT, KC_TRANSPARENT, MOON_LED_LEVEL, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, RGB_VAI, RGB_VAD, RCTL(RSFT(KC_UP)),
		KC_TRANSPARENT, KC_TRANSPARENT, KC_AUDIO_MUTE, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, TD(DANCE_8), LGUI(KC_TAB), LGUI(LSFT(KC_LEFT)), LGUI(LSFT(KC_RIGHT)), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, KC_MEDIA_PREV_TRACK, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT),
	[14] = LAYOUT_moonlander(
		TD(DANCE_9), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, TD(DANCE_10), KC_TRANSPARENT, KC_TRANSPARENT, TD(DANCE_13), KC_CIRC, KC_ASTR, KC_SLASH, KC_PERC, KC_LPRN, KC_RPRN,
		TD(DANCE_11), KC_MS_WH_UP, KC_HOME, KC_UP, KC_END, KC_PGUP, KC_TRANSPARENT, KC_TRANSPARENT, KC_EQUAL, KC_7, KC_8, KC_9, KC_EQUAL, KC_INSERT,
		KC_BSPACE, KC_MS_WH_DOWN, KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDOWN, TD(DANCE_12), KC_BSPACE, KC_PLUS, KC_4, KC_5, KC_6, KC_UP, KC_DELETE,
		KC_TRANSPARENT, KC_MS_WH_LEFT, KC_MS_LEFT, KC_MS_UP, KC_MS_RIGHT, KC_MS_WH_RIGHT, KC_MINUS, KC_1, KC_2, KC_3, TD(DANCE_14), TD(DANCE_15),
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_DOWN, KC_TRANSPARENT, KC_MS_BTN3, LSFT(KC_TAB), KC_0, KC_DOT, KC_COMMA, KC_DOWN, KC_SCOLON,
		KC_MS_BTN1, KC_MS_BTN2, KC_TRANSPARENT, KC_SPACE, KC_TAB, KC_ENTER),
};

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
	for (int i = 0; i < DRIVER_LED_TOTAL; i++)
	{
		HSV hsv = {
			.h = pgm_read_byte(&ledmap[layer][i][0]),
			.s = pgm_read_byte(&ledmap[layer][i][1]),
			.v = pgm_read_byte(&ledmap[layer][i][2]),
		};
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
	}
}

void rgb_matrix_indicators_user(void)
{
	if (g_suspend_state || keyboard_config.disable_layer_led)
	{
		return;
	}

	if (current_overlay.rgb != NULL) {
		current_overlay.rgb();
		return;
	}

	switch (biton32(layer_state))
	{
	case 0:
		set_layer_color(0);
		break;
	case 1:
		set_layer_color(1);
		break;
	case 2:
		set_layer_color(2);
		break;
	case 3:
		set_layer_color(3);
		break;
	case 4:
		set_layer_color(4);
		break;
	case 5:
		set_layer_color(5);
		break;
	case 6:
		set_layer_color(6);
		break;
	case 7:
		set_layer_color(7);
		break;
	case 8:
		set_layer_color(8);
		break;
	case 9:
		set_layer_color(9);
		break;
	case 10:
		set_layer_color(10);
		break;
	case 11:
		set_layer_color(11);
		break;
	case 12:
		set_layer_color(12);
		break;
	case 13:
		set_layer_color(13);
		break;
	case 14:
		set_layer_color(14);
		break;
	default:
		if (rgb_matrix_get_flags() == LED_FLAG_NONE)
			rgb_matrix_set_color_all(0, 0, 0);
		break;
	}
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
	static bool is_shift_pressed = false;

	if (keycode == KC_LSHIFT) {
		is_shift_pressed = record->event.pressed;
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

	if (record->event.key.col == 6 && record->event.key.row == 0 && is_shift_pressed) {
		unregister_code(KC_LSHIFT);
		if (!record->event.pressed) {
			open_menu();
		}
		return false;
	}

	switch (keycode)
	{
	case RGB_SLD:
		if (record->event.pressed)
		{
			rgblight_mode(1);
		}
		return false;
	}
	return true;
}

typedef struct
{
	bool is_press_action;
	uint8_t step;
} tap;

enum
{
	SINGLE_TAP = 1,
	SINGLE_HOLD,
	DOUBLE_TAP,
	DOUBLE_HOLD,
	DOUBLE_SINGLE_TAP,
	MORE_TAPS
};

static tap dance_state[16];

uint8_t dance_step(qk_tap_dance_state_t *state);

uint8_t dance_step(qk_tap_dance_state_t *state)
{
	if (state->count == 1)
	{
		if (state->interrupted || !state->pressed)
			return SINGLE_TAP;
		else
			return SINGLE_HOLD;
	}
	else if (state->count == 2)
	{
		if (state->interrupted)
			return DOUBLE_SINGLE_TAP;
		else if (state->pressed)
			return DOUBLE_HOLD;
		else
			return DOUBLE_TAP;
	}
	return MORE_TAPS;
}

void on_dance_0(qk_tap_dance_state_t *state, void *user_data);
void dance_0_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_0_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_0(qk_tap_dance_state_t *state, void *user_data)
{
	if (state->count == 3)
	{
		tap_code16(KC_ESCAPE);
		tap_code16(KC_ESCAPE);
		tap_code16(KC_ESCAPE);
	}
	if (state->count > 3)
	{
		tap_code16(KC_ESCAPE);
	}
}

void dance_0_finished(qk_tap_dance_state_t *state, void *user_data)
{
	dance_state[0].step = dance_step(state);
	switch (dance_state[0].step)
	{
	case SINGLE_TAP:
		register_code16(KC_ESCAPE);
		break;
	case SINGLE_HOLD:
		layer_on(8);
		break;
	case DOUBLE_TAP:
		register_code16(LCTL(KC_W));
		break;
	case DOUBLE_SINGLE_TAP:
		tap_code16(KC_ESCAPE);
		register_code16(KC_ESCAPE);
	}
}

void dance_0_reset(qk_tap_dance_state_t *state, void *user_data)
{
	wait_ms(10);
	switch (dance_state[0].step)
	{
	case SINGLE_TAP:
		unregister_code16(KC_ESCAPE);
		break;
	case SINGLE_HOLD:
		layer_off(8);
		break;
	case DOUBLE_TAP:
		unregister_code16(LCTL(KC_W));
		break;
	case DOUBLE_SINGLE_TAP:
		unregister_code16(KC_ESCAPE);
		break;
	}
	dance_state[0].step = 0;
}
void dance_1_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_1_reset(qk_tap_dance_state_t *state, void *user_data);

void dance_1_finished(qk_tap_dance_state_t *state, void *user_data)
{
	dance_state[1].step = dance_step(state);
	switch (dance_state[1].step)
	{
	case SINGLE_HOLD:
		register_code16(KC_LCTRL);
		break;
	case DOUBLE_HOLD:
		register_code16(KC_LALT);
		break;
	}
}

void dance_1_reset(qk_tap_dance_state_t *state, void *user_data)
{
	wait_ms(10);
	switch (dance_state[1].step)
	{
	case SINGLE_HOLD:
		unregister_code16(KC_LCTRL);
		break;
	case DOUBLE_HOLD:
		unregister_code16(KC_LALT);
		break;
	}
	dance_state[1].step = 0;
}
void on_dance_2(qk_tap_dance_state_t *state, void *user_data);
void dance_2_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_2_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_2(qk_tap_dance_state_t *state, void *user_data)
{
	if (state->count == 3)
	{
		tap_code16(LSFT(KC_TAB));
		tap_code16(LSFT(KC_TAB));
		tap_code16(LSFT(KC_TAB));
	}
	if (state->count > 3)
	{
		tap_code16(LSFT(KC_TAB));
	}
}

void dance_2_finished(qk_tap_dance_state_t *state, void *user_data)
{
	dance_state[2].step = dance_step(state);
	switch (dance_state[2].step)
	{
	case SINGLE_TAP:
		register_code16(LSFT(KC_TAB));
		break;
	case DOUBLE_TAP:
		register_code16(LSFT(KC_TAB));
		register_code16(LSFT(KC_TAB));
		break;
	case DOUBLE_HOLD:
		layer_move(0);
		break;
	case DOUBLE_SINGLE_TAP:
		tap_code16(LSFT(KC_TAB));
		register_code16(LSFT(KC_TAB));
	}
}

void dance_2_reset(qk_tap_dance_state_t *state, void *user_data)
{
	wait_ms(10);
	switch (dance_state[2].step)
	{
	case SINGLE_TAP:
		unregister_code16(LSFT(KC_TAB));
		break;
	case DOUBLE_TAP:
		unregister_code16(LSFT(KC_TAB));
		break;
	case DOUBLE_SINGLE_TAP:
		unregister_code16(LSFT(KC_TAB));
		break;
	}
	dance_state[2].step = 0;
}
void on_dance_3(qk_tap_dance_state_t *state, void *user_data);
void dance_3_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_3_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_3(qk_tap_dance_state_t *state, void *user_data)
{
	if (state->count == 3)
	{
		tap_code16(KC_PSCREEN);
		tap_code16(KC_PSCREEN);
		tap_code16(KC_PSCREEN);
	}
	if (state->count > 3)
	{
		tap_code16(KC_PSCREEN);
	}
}

void dance_3_finished(qk_tap_dance_state_t *state, void *user_data)
{
	dance_state[3].step = dance_step(state);
	switch (dance_state[3].step)
	{
	case SINGLE_TAP:
		register_code16(KC_PSCREEN);
		break;
	case SINGLE_HOLD:
		register_code16(LSFT(KC_PSCREEN));
		break;
	case DOUBLE_TAP:
		register_code16(LCTL(KC_PSCREEN));
		break;
	case DOUBLE_HOLD:
		register_code16(LCTL(LSFT(KC_PSCREEN)));
		break;
	case DOUBLE_SINGLE_TAP:
		tap_code16(KC_PSCREEN);
		register_code16(KC_PSCREEN);
	}
}

void dance_3_reset(qk_tap_dance_state_t *state, void *user_data)
{
	wait_ms(10);
	switch (dance_state[3].step)
	{
	case SINGLE_TAP:
		unregister_code16(KC_PSCREEN);
		break;
	case SINGLE_HOLD:
		unregister_code16(LSFT(KC_PSCREEN));
		break;
	case DOUBLE_TAP:
		unregister_code16(LCTL(KC_PSCREEN));
		break;
	case DOUBLE_HOLD:
		unregister_code16(LCTL(LSFT(KC_PSCREEN)));
		break;
	case DOUBLE_SINGLE_TAP:
		unregister_code16(KC_PSCREEN);
		break;
	}
	dance_state[3].step = 0;
}
void on_dance_4(qk_tap_dance_state_t *state, void *user_data);
void dance_4_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_4_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_4(qk_tap_dance_state_t *state, void *user_data)
{
	if (state->count == 3)
	{
		tap_code16(KC_PSCREEN);
		tap_code16(KC_PSCREEN);
		tap_code16(KC_PSCREEN);
	}
	if (state->count > 3)
	{
		tap_code16(KC_PSCREEN);
	}
}

void dance_4_finished(qk_tap_dance_state_t *state, void *user_data)
{
	dance_state[4].step = dance_step(state);
	switch (dance_state[4].step)
	{
	case SINGLE_TAP:
		register_code16(KC_PSCREEN);
		break;
	case SINGLE_HOLD:
		register_code16(LSFT(KC_PSCREEN));
		break;
	case DOUBLE_TAP:
		register_code16(LCTL(KC_PSCREEN));
		break;
	case DOUBLE_HOLD:
		register_code16(LCTL(LSFT(KC_PSCREEN)));
		break;
	case DOUBLE_SINGLE_TAP:
		tap_code16(KC_PSCREEN);
		register_code16(KC_PSCREEN);
	}
}

void dance_4_reset(qk_tap_dance_state_t *state, void *user_data)
{
	wait_ms(10);
	switch (dance_state[4].step)
	{
	case SINGLE_TAP:
		unregister_code16(KC_PSCREEN);
		break;
	case SINGLE_HOLD:
		unregister_code16(LSFT(KC_PSCREEN));
		break;
	case DOUBLE_TAP:
		unregister_code16(LCTL(KC_PSCREEN));
		break;
	case DOUBLE_HOLD:
		unregister_code16(LCTL(LSFT(KC_PSCREEN)));
		break;
	case DOUBLE_SINGLE_TAP:
		unregister_code16(KC_PSCREEN);
		break;
	}
	dance_state[4].step = 0;
}
void on_dance_5(qk_tap_dance_state_t *state, void *user_data);
void dance_5_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_5_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_5(qk_tap_dance_state_t *state, void *user_data)
{
	if (state->count == 3)
	{
		tap_code16(KC_DELETE);
		tap_code16(KC_DELETE);
		tap_code16(KC_DELETE);
	}
	if (state->count > 3)
	{
		tap_code16(KC_DELETE);
	}
}

void dance_5_finished(qk_tap_dance_state_t *state, void *user_data)
{
	dance_state[5].step = dance_step(state);
	switch (dance_state[5].step)
	{
	case SINGLE_TAP:
		register_code16(KC_DELETE);
		break;
	case SINGLE_HOLD:
		register_code16(LSFT(KC_DELETE));
		break;
	case DOUBLE_TAP:
		register_code16(LALT(LCTL(KC_DELETE)));
		break;
	case DOUBLE_SINGLE_TAP:
		tap_code16(KC_DELETE);
		register_code16(KC_DELETE);
	}
}

void dance_5_reset(qk_tap_dance_state_t *state, void *user_data)
{
	wait_ms(10);
	switch (dance_state[5].step)
	{
	case SINGLE_TAP:
		unregister_code16(KC_DELETE);
		break;
	case SINGLE_HOLD:
		unregister_code16(LSFT(KC_DELETE));
		break;
	case DOUBLE_TAP:
		unregister_code16(LALT(LCTL(KC_DELETE)));
		break;
	case DOUBLE_SINGLE_TAP:
		unregister_code16(KC_DELETE);
		break;
	}
	dance_state[5].step = 0;
}
void on_dance_6(qk_tap_dance_state_t *state, void *user_data);
void dance_6_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_6_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_6(qk_tap_dance_state_t *state, void *user_data)
{
	if (state->count == 3)
	{
		tap_code16(LCTL(LSFT(KC_ESCAPE)));
		tap_code16(LCTL(LSFT(KC_ESCAPE)));
		tap_code16(LCTL(LSFT(KC_ESCAPE)));
	}
	if (state->count > 3)
	{
		tap_code16(LCTL(LSFT(KC_ESCAPE)));
	}
}

void dance_6_finished(qk_tap_dance_state_t *state, void *user_data)
{
	dance_state[6].step = dance_step(state);
	switch (dance_state[6].step)
	{
	case SINGLE_TAP:
		register_code16(LCTL(LSFT(KC_ESCAPE)));
		break;
	case DOUBLE_TAP:
		register_code16(LALT(LCTL(KC_DELETE)));
		break;
	case DOUBLE_SINGLE_TAP:
		tap_code16(LCTL(LSFT(KC_ESCAPE)));
		register_code16(LCTL(LSFT(KC_ESCAPE)));
	}
}

void dance_6_reset(qk_tap_dance_state_t *state, void *user_data)
{
	wait_ms(10);
	switch (dance_state[6].step)
	{
	case SINGLE_TAP:
		unregister_code16(LCTL(LSFT(KC_ESCAPE)));
		break;
	case DOUBLE_TAP:
		unregister_code16(LALT(LCTL(KC_DELETE)));
		break;
	case DOUBLE_SINGLE_TAP:
		unregister_code16(LCTL(LSFT(KC_ESCAPE)));
		break;
	}
	dance_state[6].step = 0;
}
void on_dance_7(qk_tap_dance_state_t *state, void *user_data);
void dance_7_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_7_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_7(qk_tap_dance_state_t *state, void *user_data)
{
	if (state->count == 3)
	{
		tap_code16(KC_PSCREEN);
		tap_code16(KC_PSCREEN);
		tap_code16(KC_PSCREEN);
	}
	if (state->count > 3)
	{
		tap_code16(KC_PSCREEN);
	}
}

void dance_7_finished(qk_tap_dance_state_t *state, void *user_data)
{
	dance_state[7].step = dance_step(state);
	switch (dance_state[7].step)
	{
	case SINGLE_TAP:
		register_code16(KC_PSCREEN);
		break;
	case SINGLE_HOLD:
		register_code16(LSFT(KC_PSCREEN));
		break;
	case DOUBLE_TAP:
		register_code16(LCTL(KC_PSCREEN));
		break;
	case DOUBLE_SINGLE_TAP:
		tap_code16(KC_PSCREEN);
		register_code16(KC_PSCREEN);
	}
}

void dance_7_reset(qk_tap_dance_state_t *state, void *user_data)
{
	wait_ms(10);
	switch (dance_state[7].step)
	{
	case SINGLE_TAP:
		unregister_code16(KC_PSCREEN);
		break;
	case SINGLE_HOLD:
		unregister_code16(LSFT(KC_PSCREEN));
		break;
	case DOUBLE_TAP:
		unregister_code16(LCTL(KC_PSCREEN));
		break;
	case DOUBLE_SINGLE_TAP:
		unregister_code16(KC_PSCREEN);
		break;
	}
	dance_state[7].step = 0;
}
void on_dance_8(qk_tap_dance_state_t *state, void *user_data);
void dance_8_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_8_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_8(qk_tap_dance_state_t *state, void *user_data)
{
	if (state->count == 3)
	{
		tap_code16(LALT(KC_TAB));
		tap_code16(LALT(KC_TAB));
		tap_code16(LALT(KC_TAB));
	}
	if (state->count > 3)
	{
		tap_code16(LALT(KC_TAB));
	}
}

void dance_8_finished(qk_tap_dance_state_t *state, void *user_data)
{
	dance_state[8].step = dance_step(state);
	switch (dance_state[8].step)
	{
	case SINGLE_TAP:
		register_code16(LALT(KC_TAB));
		break;
	case DOUBLE_TAP:
		register_code16(LGUI(KC_TAB));
		break;
	case DOUBLE_SINGLE_TAP:
		tap_code16(LALT(KC_TAB));
		register_code16(LALT(KC_TAB));
	}
}

void dance_8_reset(qk_tap_dance_state_t *state, void *user_data)
{
	wait_ms(10);
	switch (dance_state[8].step)
	{
	case SINGLE_TAP:
		unregister_code16(LALT(KC_TAB));
		break;
	case DOUBLE_TAP:
		unregister_code16(LGUI(KC_TAB));
		break;
	case DOUBLE_SINGLE_TAP:
		unregister_code16(LALT(KC_TAB));
		break;
	}
	dance_state[8].step = 0;
}
void on_dance_9(qk_tap_dance_state_t *state, void *user_data);
void dance_9_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_9_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_9(qk_tap_dance_state_t *state, void *user_data)
{
	if (state->count == 3)
	{
		tap_code16(KC_ESCAPE);
		tap_code16(KC_ESCAPE);
		tap_code16(KC_ESCAPE);
	}
	if (state->count > 3)
	{
		tap_code16(KC_ESCAPE);
	}
}

void dance_9_finished(qk_tap_dance_state_t *state, void *user_data)
{
	dance_state[9].step = dance_step(state);
	switch (dance_state[9].step)
	{
	case SINGLE_TAP:
		register_code16(KC_ESCAPE);
		break;
	case DOUBLE_TAP:
		register_code16(LCTL(KC_W));
		break;
	case DOUBLE_SINGLE_TAP:
		tap_code16(KC_ESCAPE);
		register_code16(KC_ESCAPE);
	}
}

void dance_9_reset(qk_tap_dance_state_t *state, void *user_data)
{
	wait_ms(10);
	switch (dance_state[9].step)
	{
	case SINGLE_TAP:
		unregister_code16(KC_ESCAPE);
		break;
	case DOUBLE_TAP:
		unregister_code16(LCTL(KC_W));
		break;
	case DOUBLE_SINGLE_TAP:
		unregister_code16(KC_ESCAPE);
		break;
	}
	dance_state[9].step = 0;
}
void dance_10_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_10_reset(qk_tap_dance_state_t *state, void *user_data);

void dance_10_finished(qk_tap_dance_state_t *state, void *user_data)
{
	dance_state[10].step = dance_step(state);
	switch (dance_state[10].step)
	{
	case DOUBLE_TAP:
		register_code16(LALT(KC_F4));
		break;
	}
}

void dance_10_reset(qk_tap_dance_state_t *state, void *user_data)
{
	wait_ms(10);
	switch (dance_state[10].step)
	{
	case DOUBLE_TAP:
		unregister_code16(LALT(KC_F4));
		break;
	}
	dance_state[10].step = 0;
}
void on_dance_11(qk_tap_dance_state_t *state, void *user_data);
void dance_11_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_11_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_11(qk_tap_dance_state_t *state, void *user_data)
{
	if (state->count == 3)
	{
		tap_code16(KC_TAB);
		tap_code16(KC_TAB);
		tap_code16(KC_TAB);
	}
	if (state->count > 3)
	{
		tap_code16(KC_TAB);
	}
}

void dance_11_finished(qk_tap_dance_state_t *state, void *user_data)
{
	dance_state[11].step = dance_step(state);
	switch (dance_state[11].step)
	{
	case SINGLE_TAP:
		register_code16(KC_TAB);
		break;
	case DOUBLE_TAP:
		register_code16(LALT(KC_TAB));
		break;
	case DOUBLE_SINGLE_TAP:
		tap_code16(KC_TAB);
		register_code16(KC_TAB);
	}
}

void dance_11_reset(qk_tap_dance_state_t *state, void *user_data)
{
	wait_ms(10);
	switch (dance_state[11].step)
	{
	case SINGLE_TAP:
		unregister_code16(KC_TAB);
		break;
	case DOUBLE_TAP:
		unregister_code16(LALT(KC_TAB));
		break;
	case DOUBLE_SINGLE_TAP:
		unregister_code16(KC_TAB);
		break;
	}
	dance_state[11].step = 0;
}
void on_dance_12(qk_tap_dance_state_t *state, void *user_data);
void dance_12_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_12_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_12(qk_tap_dance_state_t *state, void *user_data)
{
	if (state->count == 3)
	{
		tap_code16(KC_DELETE);
		tap_code16(KC_DELETE);
		tap_code16(KC_DELETE);
	}
	if (state->count > 3)
	{
		tap_code16(KC_DELETE);
	}
}

void dance_12_finished(qk_tap_dance_state_t *state, void *user_data)
{
	dance_state[12].step = dance_step(state);
	switch (dance_state[12].step)
	{
	case SINGLE_TAP:
		register_code16(KC_DELETE);
		break;
	case SINGLE_HOLD:
		register_code16(LSFT(KC_DELETE));
		break;
	case DOUBLE_TAP:
		register_code16(LALT(LCTL(KC_DELETE)));
		break;
	case DOUBLE_SINGLE_TAP:
		tap_code16(KC_DELETE);
		register_code16(KC_DELETE);
	}
}

void dance_12_reset(qk_tap_dance_state_t *state, void *user_data)
{
	wait_ms(10);
	switch (dance_state[12].step)
	{
	case SINGLE_TAP:
		unregister_code16(KC_DELETE);
		break;
	case SINGLE_HOLD:
		unregister_code16(LSFT(KC_DELETE));
		break;
	case DOUBLE_TAP:
		unregister_code16(LALT(LCTL(KC_DELETE)));
		break;
	case DOUBLE_SINGLE_TAP:
		unregister_code16(KC_DELETE);
		break;
	}
	dance_state[12].step = 0;
}
void on_dance_13(qk_tap_dance_state_t *state, void *user_data);
void dance_13_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_13_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_13(qk_tap_dance_state_t *state, void *user_data)
{
	if (state->count == 3)
	{
		tap_code16(KC_ESCAPE);
		tap_code16(KC_ESCAPE);
		tap_code16(KC_ESCAPE);
	}
	if (state->count > 3)
	{
		tap_code16(KC_ESCAPE);
	}
}

void dance_13_finished(qk_tap_dance_state_t *state, void *user_data)
{
	dance_state[13].step = dance_step(state);
	switch (dance_state[13].step)
	{
	case SINGLE_TAP:
		register_code16(KC_ESCAPE);
		break;
	case DOUBLE_TAP:
		register_code16(KC_CALCULATOR);
		break;
	case DOUBLE_SINGLE_TAP:
		tap_code16(KC_ESCAPE);
		register_code16(KC_ESCAPE);
	}
}

void dance_13_reset(qk_tap_dance_state_t *state, void *user_data)
{
	wait_ms(10);
	switch (dance_state[13].step)
	{
	case SINGLE_TAP:
		unregister_code16(KC_ESCAPE);
		break;
	case DOUBLE_TAP:
		unregister_code16(KC_CALCULATOR);
		break;
	case DOUBLE_SINGLE_TAP:
		unregister_code16(KC_ESCAPE);
		break;
	}
	dance_state[13].step = 0;
}
void on_dance_14(qk_tap_dance_state_t *state, void *user_data);
void dance_14_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_14_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_14(qk_tap_dance_state_t *state, void *user_data)
{
	if (state->count == 3)
	{
		tap_code16(KC_LEFT);
		tap_code16(KC_LEFT);
		tap_code16(KC_LEFT);
	}
	if (state->count > 3)
	{
		tap_code16(KC_LEFT);
	}
}

void dance_14_finished(qk_tap_dance_state_t *state, void *user_data)
{
	dance_state[14].step = dance_step(state);
	switch (dance_state[14].step)
	{
	case SINGLE_TAP:
		register_code16(KC_LEFT);
		break;
	case SINGLE_HOLD:
		register_code16(KC_HOME);
		break;
	case DOUBLE_TAP:
		register_code16(KC_LEFT);
		register_code16(KC_LEFT);
		break;
	case DOUBLE_SINGLE_TAP:
		tap_code16(KC_LEFT);
		register_code16(KC_LEFT);
	}
}

void dance_14_reset(qk_tap_dance_state_t *state, void *user_data)
{
	wait_ms(10);
	switch (dance_state[14].step)
	{
	case SINGLE_TAP:
		unregister_code16(KC_LEFT);
		break;
	case SINGLE_HOLD:
		unregister_code16(KC_HOME);
		break;
	case DOUBLE_TAP:
		unregister_code16(KC_LEFT);
		break;
	case DOUBLE_SINGLE_TAP:
		unregister_code16(KC_LEFT);
		break;
	}
	dance_state[14].step = 0;
}
void on_dance_15(qk_tap_dance_state_t *state, void *user_data);
void dance_15_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_15_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_15(qk_tap_dance_state_t *state, void *user_data)
{
	if (state->count == 3)
	{
		tap_code16(KC_RIGHT);
		tap_code16(KC_RIGHT);
		tap_code16(KC_RIGHT);
	}
	if (state->count > 3)
	{
		tap_code16(KC_RIGHT);
	}
}

void dance_15_finished(qk_tap_dance_state_t *state, void *user_data)
{
	dance_state[15].step = dance_step(state);
	switch (dance_state[15].step)
	{
	case SINGLE_TAP:
		register_code16(KC_RIGHT);
		break;
	case SINGLE_HOLD:
		register_code16(KC_END);
		break;
	case DOUBLE_TAP:
		register_code16(KC_RIGHT);
		register_code16(KC_RIGHT);
		break;
	case DOUBLE_SINGLE_TAP:
		tap_code16(KC_RIGHT);
		register_code16(KC_RIGHT);
	}
}

void dance_15_reset(qk_tap_dance_state_t *state, void *user_data)
{
	wait_ms(10);
	switch (dance_state[15].step)
	{
	case SINGLE_TAP:
		unregister_code16(KC_RIGHT);
		break;
	case SINGLE_HOLD:
		unregister_code16(KC_END);
		break;
	case DOUBLE_TAP:
		unregister_code16(KC_RIGHT);
		break;
	case DOUBLE_SINGLE_TAP:
		unregister_code16(KC_RIGHT);
		break;
	}
	dance_state[15].step = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
	[DANCE_0] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_0, dance_0_finished, dance_0_reset),
	[DANCE_1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_1_finished, dance_1_reset),
	[DANCE_2] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_2, dance_2_finished, dance_2_reset),
	[DANCE_3] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_3, dance_3_finished, dance_3_reset),
	[DANCE_4] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_4, dance_4_finished, dance_4_reset),
	[DANCE_5] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_5, dance_5_finished, dance_5_reset),
	[DANCE_6] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_6, dance_6_finished, dance_6_reset),
	[DANCE_7] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_7, dance_7_finished, dance_7_reset),
	[DANCE_8] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_8, dance_8_finished, dance_8_reset),
	[DANCE_9] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_9, dance_9_finished, dance_9_reset),
	[DANCE_10] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_10_finished, dance_10_reset),
	[DANCE_11] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_11, dance_11_finished, dance_11_reset),
	[DANCE_12] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_12, dance_12_finished, dance_12_reset),
	[DANCE_13] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_13, dance_13_finished, dance_13_reset),
	[DANCE_14] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_14, dance_14_finished, dance_14_reset),
	[DANCE_15] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_15, dance_15_finished, dance_15_reset),
};
