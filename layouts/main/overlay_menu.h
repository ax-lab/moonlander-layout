#pragma once

bool menu_overlay_process(uint16_t keycode, keyrecord_t *record)
{
	if (!record->event.pressed) {
		return false;
	}

	switch (keycode) {
	case KC_1:
		open_rainbow();
		break;
	case KC_2:
		open_simple_snake();
		break;
	default:
		close_overlay();
	}
	return false;
}

void menu_overlay_rgb(void)
{
	clear_led_matrix();

	const uint8_t number_row = 0;
	for (uint8_t col = 1; col <= 12; col++) {
		if (col <= 5 || col >= 8) {
			led_set_by_pos_hsv(number_row, col, C_ORANGE);
		}
	}
}

static overlay_t menu_overlay = {
	.process = menu_overlay_process,
	.rgb = menu_overlay_rgb,
};

void open_menu(void)
{
	open_overlay(menu_overlay);
}
