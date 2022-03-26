#pragma once

#define MENU_RESET_ROW 6
#define MENU_RESET_COL 6

bool menu_overlay_process(uint16_t keycode, keyrecord_t *record)
{
	uint8_t row = record->event.key.row;
	uint8_t col = record->event.key.col;
	switch (keycode) {
	case KC_1:
		open_pong();
		break;
	case KC_2:
		open_rainbow();
		break;
	case KC_3:
		open_simple_snake();
		break;
	default:
		if (row == MENU_RESET_ROW && col == MENU_RESET_COL) {
			bootloader_jump();
			return false;
		}
		close_overlay();
	}
	return false;
}

void menu_overlay_rgb(void)
{
	clear_led_matrix();

	for (uint8_t col = 1; col <= 12; col++) {
		if (col <= 5 || col >= 8) {
			led_set_by_pos_hsv(0, col, C_ORANGE);
		}
	}

	led_set_by_row_col_hsv(MENU_RESET_ROW, MENU_RESET_COL, C_RED);
}

static overlay_t menu_overlay = {
	.process = menu_overlay_process,
	.rgb = menu_overlay_rgb,
};

void open_menu(void)
{
	open_overlay(menu_overlay);
}
