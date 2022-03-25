#pragma once

HSV rainbow_color_for_position(uint8_t row, uint8_t col, bool print)
{
	uint8_t max = MATRIX_COLS * MATRIX_ROWS;
	uint8_t pos = row * MATRIX_COLS + col;
	uint8_t v = ((float)pos / (max - 1)) * 0xFF;
	HSV hsv = { v, 255, 255 };
	if (print) {
		RGB rgb = hsv_to_rgb(hsv);
		output("HUE = %d / RGB: #%02X%02X%02X\n", v, rgb.r, rgb.g, rgb.b);
	}
	return hsv;
}

bool rainbow_overlay_process(uint16_t keycode, keyrecord_t *record)
{
	if (record->event.pressed) {
		rainbow_color_for_position(record->event.key.row, record->event.key.col, true);
	}
	if (record->event.key.row == 0 && record->event.key.col == 0) {
		close_overlay();
	}
	return false;
}

void rainbow_overlay_rgb(void)
{
	clear_led_matrix();
	for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
		for (uint8_t col = 0; col < MATRIX_COLS; col++) {
			HSV color = rainbow_color_for_position(row, col, false);
			led_set_by_row_col_hsv(row, col, color);
		}
	}
}

static overlay_t rainbow_overlay = {
	.process = rainbow_overlay_process,
	.rgb = rainbow_overlay_rgb,
};

void open_rainbow(void)
{
	open_overlay(rainbow_overlay);
}
