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

	set_layer_color(biton32(layer_state));
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
