#pragma once

/*
	https://docs.qmk.fm/#/feature_rgblight

	256 = red
	201 = magenta
	169 = blue
	127 = cyan
	085 = green
	043 = yellow
*/

#define RED {248, 255, 255} // #FF0036
#define PNK {225, 255, 255} // #FF00BF
#define GRN { 84, 255, 255} // #0AFF00
#define BLU {139, 255, 255} // #00BFFF
#define PUR {185, 255, 255} // #5000FF
#define NAV {167, 255, 255} // #0019FF
#define ORG {  8, 255, 255} // #FF3500
#define ORY { 24, 255, 255} // #FF9100
#define YLW { 41, 255, 255} // #FFF500
#define WHI {  0,   0, 255} // #FFFFFF
#define VIO {205, 255, 255} // #C600FF

static HSV C_WHITE  = WHI;
static HSV C_RED    = RED;
static HSV C_PINK   = PNK;
static HSV C_GREEN  = GRN;
static HSV C_ORANGE = ORG;
static HSV C_YELLOW = YLW;

/**
 * Returns the index for a led respective to matrix row and column.
 */
uint8_t led_index_from_row_col(uint8_t row, uint8_t col)
{
	uint8_t index[8];
	uint8_t count = rgb_matrix_map_row_column_to_led(row, col, index);
	if (count > 0) {
		return index[0];
	}
	return NO_LED;
}

/** Number of physical rows in the keyboard. */
#define LAYOUT_ROWS 6

/** Number of physical cols in the keyboard. */
#define LAYOUT_COLS 14

/**
 * Led index for a key by its physical layout position.
 *
 * This differs from the matrix row and column in that it takes into account
 * the actual position of the keys in the physical keyboard.
 */
uint8_t led_index_from_pos(uint8_t layout_row, uint8_t layout_col) {
	if (layout_row >= LAYOUT_ROWS || layout_col >= LAYOUT_COLS) {
		return NO_LED;
	}

	// each halve of the keyboard is mapped as separate rows
	uint8_t row = layout_row;
	uint8_t col = layout_col;
	if (row == 5) {
		// the thumb cluster is considered as if aligned at the center
		// with the thumb key at the inner border of the keyboard
		switch (col) {
			case 3:
			case 4:
			case 5:
			case 6:
				col -= 3;
				break;
			case 7:
			case 8:
			case 9:
			case 10:
				row = 11;
				col -= 4;
				break;
			default:
				return NO_LED;
		}
	} else if (col >= 7) {
		col -= 7;
		row += 6;
	}

	return led_index_from_row_col(row, col);
}

void clear_led_matrix(void)
{
	for (int i = 0; i < DRIVER_LED_TOTAL; i++)
	{
		rgb_matrix_set_color(i, 0, 0, 0);
	}
}

bool led_set_by_row_col_hsv(uint8_t row, uint8_t col, HSV hsv)
{
	uint8_t index = led_index_from_row_col(row, col);
	if (index != NO_LED) {
		float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
		RGB rgb = hsv_to_rgb(hsv);
		rgb_matrix_set_color(index, f * rgb.r, f * rgb.g, f * rgb.b);
		return true;
	}
	return false;
}

bool led_set_by_pos_hsv(uint8_t row, uint8_t col, HSV hsv)
{
	uint8_t index = led_index_from_pos(row, col);
	if (index != NO_LED) {
		float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
		RGB rgb = hsv_to_rgb(hsv);
		rgb_matrix_set_color(index, f * rgb.r, f * rgb.g, f * rgb.b);
		return true;
	}
	return false;
}
