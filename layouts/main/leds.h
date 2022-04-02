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

/*
	LED layout:

	+------------------------+   +------------------------+
	|  A0 B0 C0 D0 E0 F0 G0  |   |  H0 I0 J0 K0 L0 M0 N0  |
	|  A1 B1 C1 D1 E1 F1 G1  |   |  H1 I1 J1 K1 L1 M1 N1  |
	|  A2 B2 C2 D2 E2 F2 G2  |   |  H2 I2 J2 K2 L2 M2 N2  |
	|  A3 B3 C3 D3 E3 F3     |   |     I3 J3 K3 L3 M3 N3  |
	|  A4 B4 C4 D4 E4    X3  |   |  Y3    J4 K4 L4 M4 N4  |
	|              X0 X1 X2  |   |  Y2 Y1 Y0              |
	+------------------------+   +------------------------+
*/

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
	//      A0   A1   A2   A3   A4   B0   B1   B2   B3   B4   C0   C1   C2   C3   C4   D0   D1   D2   D3   D4   E0   E1   E2   E3   E4   F0   F1   F2   F3   G0   G1   G2   X0   X1   X2   X3   N0   N1   N2   N3   N4   M0   M1   M2   M3   M4   L0   L1   L2   L3   L4   K0   K1   K2   K3   K4   J0   J1   J2   J3   J4   I0   I1   I2   I3   H0   H1   H2   Y0   Y1   Y2   Y3
	[0]  = {ORG, RED, RED, RED, RED, RED, PNK, PNK, PNK, RED, RED, PNK, PNK, PNK, RED, RED, PNK, PNK, PNK, RED, RED, PNK, PNK, PNK, RED, RED, PNK, PNK, PNK, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, PNK, PNK, PNK, RED, RED, PNK, PNK, PNK, RED, RED, PNK, PNK, PNK, RED, RED, PNK, PNK, PNK, RED, RED, PNK, PNK, PNK, RED, RED, RED, RED, RED, RED, RED},
	[1]  = {RED, PNK, GRN, GRN, PNK, PNK, PNK, BLU, PNK, GRN, PNK, BLU, BLU, PNK, PNK, PNK, PNK, BLU, PNK, ORY, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, RED, PNK, PNK, ORY, GRN, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, BLU, PNK, PNK, PNK, BLU, BLU, PNK, PNK, PNK, PNK, BLU, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, ORY},
	[2]  = {BLU, BLU, BLU, GRN, GRN, BLU, BLU, BLU, GRN, GRN, PUR, PUR, PUR, NAV, NAV, PUR, PUR, PUR, NAV, NAV, PNK, PNK, PNK, ORG, ORG, PNK, PNK, PNK, ORG, RED, RED, RED, BLU, BLU, BLU, BLU, NAV, NAV, NAV, BLU, BLU, NAV, NAV, NAV, BLU, BLU, GRN, GRN, GRN, PUR, PUR, GRN, GRN, GRN, PUR, PUR, ORG, ORG, ORG, PNK, PNK, ORG, ORG, ORG, PNK, RED, RED, RED, BLU, BLU, BLU, WHI},
	[3]  = {PNK, PNK, PNK, PNK, PNK, PNK, PNK, GRN, PNK, PNK, PNK, PNK, GRN, PNK, PNK, PNK, PNK, GRN, PNK, PNK, PNK, PNK, GRN, PNK, PNK, PNK, PNK, PNK, PNK, PNK, YLW, BLU, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, GRN, PNK, PNK, PNK, PNK, GRN, ORY, PNK, PNK, PNK, GRN, ORY, PNK, PNK, PNK, GRN, ORY, PNK, PNK, PNK, PNK, PNK, PNK, YLW, BLU, PNK, PNK, PNK, PNK},
	[4]  = {PNK, PNK, PNK, PNK, PNK, ORY, PNK, PNK, PNK, PNK, ORY, PNK, PNK, PNK, PNK, ORY, PNK, PNK, PNK, RED, ORY, PNK, PNK, PNK, RED, ORY, PNK, PNK, PNK, PNK, PNK, RED, PNK, GRN, GRN, RED, ORY, ORY, PNK, PNK, PNK, ORY, PNK, PNK, PNK, PNK, ORY, PNK, PNK, PNK, PNK, ORY, PNK, PNK, PNK, PNK, ORY, PNK, PNK, PNK, PNK, ORY, PNK, PNK, PNK, PNK, PNK, RED, PNK, PNK, PNK, PNK},
	[5]  = {RED, BLU, RED, RED, RED, RED, PNK, YLW, PNK, RED, RED, PNK, YLW, PNK, RED, RED, PNK, YLW, PNK, GRN, RED, PNK, YLW, PNK, RED, RED, PNK, YLW, PNK, RED, BLU, PNK, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, PNK, YLW, PNK, RED, RED, PNK, YLW, PNK, RED, RED, PNK, YLW, PNK, RED, RED, PNK, YLW, YLW, RED, RED, PNK, PNK, PNK, RED, RED, RED, RED, RED, RED, RED},
	[6]  = {BLU, BLU, PNK, BLU, BLU, PNK, BLU, ORY, PNK, PNK, PNK, ORY, BLU, ORY, PNK, PNK, BLU, BLU, ORY, PNK, PNK, ORY, BLU, ORY, PNK, PNK, PNK, ORY, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, GRN, PNK, PNK, PNK, BLU, GRN, PNK, PNK, PNK, BLU, GRN, BLU, PNK, PNK, BLU, GRN, BLU, GRN, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK},
	[7]  = {BLU, PNK, PNK, PNK, BLU, ORY, ORY, GRN, PNK, PNK, ORY, ORY, GRN, PNK, PNK, ORY, ORY, GRN, PNK, PNK, ORY, ORY, GRN, PNK, PNK, ORY, ORY, PNK, PNK, YLW, YLW, ORY, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, YLW, YLW, YLW, PNK, PNK, ORY, ORY, ORY, PNK, PNK, ORY, ORY, ORY, PNK, PNK, ORY, ORY, ORY, PNK, PNK, YLW, YLW, YLW, PNK, PNK, BLU, PNK, PNK, PNK, PNK},
	[8]  = {PNK, PNK, PNK, PNK, PNK, ORY, ORY, ORY, ORY, PNK, PNK, ORY, ORY, ORY, PNK, PNK, PNK, ORY, ORY, PNK, ORY, ORY, ORY, ORY, PNK, ORY, ORY, ORY, ORY, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, ORY, ORY, ORY, ORY, PNK, PNK, PNK, ORY, PNK, PNK, ORY, ORY, ORY, ORY, PNK, PNK, PNK, ORY, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK},
	[9]  = {WHI, PNK, YLW, PNK, PNK, ORY, YLW, YLW, YLW, PNK, ORY, YLW, YLW, YLW, PNK, ORY, YLW, YLW, YLW, PNK, ORY, PNK, BLU, BLU, PNK, ORY, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, ORY, ORY, PNK, PNK, PNK, ORY, PNK, PNK, PNK, PNK, ORY, PNK, PNK, PNK, PNK, ORY, PNK, PNK, PNK, PNK, ORY, PNK, PNK, PNK, PNK, ORY, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK},
	[10] = {PNK, YLW, YLW, YLW, PNK, PNK, ORY, ORY, ORY, PNK, PNK, ORY, ORY, ORY, PNK, PNK, ORY, ORY, ORY, PNK, PNK, PNK, BLU, PNK, PNK, PNK, BLU, BLU, BLU, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK},
	[11] = {ORY, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, PNK, RED, PNK, PNK, RED, PNK, BLU, PNK, PNK, ORY, RED, BLU, PNK, PNK, ORY, PNK, PNK, PNK, PNK, PNK, PNK, YLW, GRN, ORY, ORY, BLU, RED, PNK, PNK, BLU, WHI, GRN, YLW, YLW, YLW, PNK, PNK, PNK, PNK, YLW, PNK, PNK, PNK, PNK, PNK, BLU, PNK, RED, RED, PNK, BLU, PNK, ORY, ORY, PNK, WHI, GRN, GRN, PNK, PNK, PNK, BLU},
	[12] = {RED, PNK, RED, PNK, PNK, PNK, ORY, ORY, ORY, PNK, PNK, PNK, BLU, BLU, PNK, PNK, BLU, BLU, BLU, BLU, RED, PNK, BLU, BLU, PNK, PNK, PNK, PNK, ORY, PNK, WHI, RED, ORY, ORY, PNK, ORY, YLW, ORY, RED, BLU, PNK, YLW, PNK, BLU, BLU, BLU, PNK, YLW, YLW, YLW, PNK, PNK, YLW, YLW, YLW, PNK, PNK, YLW, YLW, YLW, YLW, PNK, PNK, PNK, PNK, VIO, WHI, RED, PNK, BLU, ORY, BLU},
};

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
