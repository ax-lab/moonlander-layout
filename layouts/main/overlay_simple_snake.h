#pragma once

#define SIMPLE_SNAKE_DELAY_MS 125

static struct {
	uint32_t timer;
	uint8_t row;
	uint8_t col;
} simple_snake_state = { 0 };

bool simple_snake_overlay_process(uint16_t keycode, keyrecord_t *record)
{
	if (record->event.pressed) {
		close_overlay();
	}
	return false;
}

void simple_snake_overlay_rgb(void)
{
	clear_led_matrix();

	if (timer_elapsed32(simple_snake_state.timer) >= SIMPLE_SNAKE_DELAY_MS) {
		simple_snake_state.col++;
		if (simple_snake_state.col >= LAYOUT_COLS) {
			simple_snake_state.col = 0;
			simple_snake_state.row++;
		}
		if (simple_snake_state.row >= LAYOUT_ROWS) {
			close_overlay();
			return;
		} else {
			uint8_t led_index = led_index_from_pos(simple_snake_state.row, simple_snake_state.col);
			if (led_index != NO_LED) {
				simple_snake_state.timer = timer_read32();
			}
		}
	}

	HSV color = {0, 255, 255};
	led_set_by_pos_hsv(simple_snake_state.row, simple_snake_state.col, color);
}

static overlay_t simple_snake_overlay = {
	.process = simple_snake_overlay_process,
	.rgb = simple_snake_overlay_rgb,
};

void open_simple_snake(void)
{
	simple_snake_state.timer = timer_read32();
	simple_snake_state.row = 0;
	simple_snake_state.col = 0;
	open_overlay(simple_snake_overlay);
}
