#pragma once

#define PONG_TICK 10
#define PONG_ROWS (LAYOUT_ROWS - 1)
#define PONG_COLS (LAYOUT_COLS)
#define PONG_W ((double)PONG_COLS)
#define PONG_H ((double)PONG_ROWS)

#define PONG_BALL_SIZE   1.5
#define PONG_BALL_SPEED  0.04
#define PONG_SERVE_DELAY 500
#define PONG_BALL_HUE    85

#define PONG_MAX_X ((PONG_W / 2) - PONG_BALL_SIZE / 2)
#define PONG_MIN_X (-PONG_MAX_X)
#define PONG_MAX_Y ((PONG_H / 2) - PONG_BALL_SIZE / 2)
#define PONG_MIN_Y (-PONG_MAX_Y)

#define PONG_COUNTDOWN 3700
#define PONG_COUNTDOWN_FLASH_ACTIVE 700


typedef enum {
	PONG_START,
	PONG_SERVE_P1,
	PONG_SERVE_P2,
	PONG_PLAYING,
	PONG_SCORE_P1,
	PONG_SCORE_P2,
	PONG_GAME_OVER,
} pong_state_t;

static struct {
	vec_t ball_pos;
	vec_t ball_speed;
	vec_t p1_pos;
	vec_t p2_pos;

	uint32_t start;

	uint8_t score_p1;
	uint8_t score_p2;

	pong_state_t state;

	bool is_cpu_p1;
	bool is_cpu_p2;

	bool key_p1_up;
	bool key_p1_dn;
	bool key_p2_up;
	bool key_p2_dn;
} pong = { 0 };

bool pong_reflect_value(double *v, double min, double max);
void pong_draw_board(void);
void pong_draw_digit(HSV color, int digit, bool p1, bool p2);

bool pong_overlay_process(uint16_t keycode, keyrecord_t *record)
{
	close_overlay();
	return false;
}

void pong_overlay_rgb(void)
{
	clear_led_matrix();

	uint32_t now = timer_read32();

	switch (pong.state) {

	case PONG_START: {
		uint32_t start_at = pong.start + PONG_COUNTDOWN;
		if (now >= start_at) {
			pong.start = now;
			pong.state = rand() % 2 ? PONG_SERVE_P1 : PONG_SERVE_P2;
		} else {
			uint32_t countdown = start_at - now;
			bool show_digit = countdown >= 1000 && (countdown % 1000) < PONG_COUNTDOWN_FLASH_ACTIVE;
			if (show_digit) {
				pong_draw_digit(C_YELLOW, countdown / 1000, true, true);
			}
		}
		break;
	}

	case PONG_SERVE_P1:
	case PONG_SERVE_P2: {
		bool is_p1 = pong.state == PONG_SERVE_P1;
		bool is_cpu = (is_p1 && pong.is_cpu_p1) || (!is_p1 && pong.is_cpu_p2);
		pong.ball_pos.y = 0;
		pong.ball_pos.x = ((PONG_W / 2) - 1.5) * (is_p1 ? -1 : +1);
		pong.ball_speed = vec_zero();
		if (is_cpu && (now - pong.start) >= PONG_SERVE_DELAY) {
			pong.start = now;
			pong.state = PONG_PLAYING;
			pong.ball_speed.x = is_p1 ? +1 : -1;
			pong.ball_speed.y = 3 * random_double() - 1.5;
			pong.ball_speed = vec_scale(vec_norm(pong.ball_speed), PONG_BALL_SPEED);
		}

		pong_draw_board();
		break;
	}

	case PONG_PLAYING: {
		uint32_t delta = now - pong.start;
		while (delta >= PONG_TICK) {
			delta -= PONG_TICK;
			pong.start += PONG_TICK;
			pong.ball_pos = vec_add(pong.ball_pos, pong.ball_speed);
			if (pong_reflect_value(&pong.ball_pos.x, PONG_MIN_X, PONG_MAX_X)) {
				pong.ball_speed.x *= -1;
			}
			if (pong_reflect_value(&pong.ball_pos.y, PONG_MIN_Y, PONG_MAX_Y)) {
				pong.ball_speed.y *= -1;
			}
		}

		pong_draw_board();
		break;
	}

	case PONG_SCORE_P1:
		break;
	case PONG_SCORE_P2:
		break;
	case PONG_GAME_OVER:
		break;
	}
}

static overlay_t pong_overlay = {
	.process = pong_overlay_process,
	.rgb = pong_overlay_rgb,
};

void open_pong(void)
{
	zero(&pong);
	pong.start = timer_read32();
	pong.state = PONG_START;
	pong.is_cpu_p1 = true;
	pong.is_cpu_p2 = true;
	open_overlay(pong_overlay);
	srand(pong.start);
}

//----------------------------------------------------------------------------//
// Helpers
//----------------------------------------------------------------------------//

bool pong_reflect_value(double *v, double min, double max)
{
	if (*v < (min - EPSILON)) {
		*v = min + (min - *v);
		return true;
	}
	if (*v > (max + EPSILON)) {
		*v = max - (*v - max);
		return true;
	}

	return false;
}

double pong_collision_1d(double pos_a, double size_a, double pos_b, double size_b)
{
	double a1 = pos_a - size_a / 2;
	double a2 = pos_a + size_a / 2;
	double b1 = pos_b - size_b / 2;
	double b2 = pos_b + size_b / 2;
	if (b1 >= a2 || b2 <= a1) {
		return 0;
	}
	double p1 = fmax(a1, b1);
	double p2 = fmin(a2, b2);
	double overlap = p2 - p1;
	return overlap < EPSILON ? 0 : overlap;
}

double pong_collision(vec_t pos_a, double size_a, vec_t pos_b, double size_b)
{
	double dx = pong_collision_1d(pos_a.x, size_a, pos_b.x, size_b);
	double dy = pong_collision_1d(pos_a.y, size_a, pos_b.y, size_b);
	double res = dx * dy;
	return res < EPSILON ? 0 : res;
}

void pong_draw_board(void)
{
	for (uint8_t row = 0; row < PONG_ROWS; row++) {
		for (uint8_t col = 0; col < PONG_COLS; col++) {
			double x = (double)col + 0.5 - PONG_W / 2;
			double y = (double)row + 0.5 - PONG_H / 2;
			vec_t xy = {x, y};
			double area = pong_collision(pong.ball_pos, PONG_BALL_SIZE, xy, 1);
			uint8_t value = fmin(ceil(area * (double)0xFF), 0xFF);
			if (value > 0) {
				HSV color = { PONG_BALL_HUE, 255, value };
				led_set_by_pos_hsv(row, col, color);
			}
		}
	}
}

const uint16_t PROGMEM DIGITS[10] = {
	// 111222333444555
	0b0111101101101111, // 0
	0b0010110010010111, // 1
	0b0111001111100111, // 2
	0b0111001111001111, // 3
	0b0101101111001001, // 4
	0b0111100111001111, // 5
	0b0111100111101111, // 6
	0b0111001001001001, // 7
	0b0111101111101111, // 8
	0b0111101111001001, // 9
};

void pong_draw_digit(HSV color, int digit, bool p1, bool p2)
{
	const uint8_t col_p1 = 2;
	const uint8_t col_p2 = 9;
	uint16_t bits = DIGITS[digit % 10];
	uint16_t mask = 1 << 14;
	for (uint8_t row = 0; row < 5; row++) {
		for (uint8_t col = 0; col < 3; col++) {
			bool enabled = bits & mask;
			mask = mask >> 1;
			if (enabled) {
				if (p1) {
					led_set_by_pos_hsv(row, col + col_p1, color);
				}
				if (p2) {
					led_set_by_pos_hsv(row, col + col_p2, color);
				}
			}
		}
	}
}
