#pragma once

#define PONG_TICK 10
#define PONG_ROWS (LAYOUT_ROWS - 1)
#define PONG_COLS (LAYOUT_COLS)
#define PONG_W ((double)PONG_COLS)
#define PONG_H ((double)PONG_ROWS)

#define PONG_MAX_SCORE 5

#define PONG_BALL_SIZE      1.0
#define PONG_BALL_HUE       85
#define PONG_BALL_SPEED     0.06
#define PONG_BALL_SPEED_MAX 0.20

#define PONG_PAD_SIZE 1.3
#define PONG_PAD_HUE  201
#define PONG_PAD_SPEED_PLAYER 0.03
#define PONG_PAD_SPEED_CPU    0.02
#define PONG_PAD_ALIGN_GRID   false

#define PONG_SERVE_DELAY 500
#define PONG_CPU_RETURNS_TO_MIDDLE false
#define PONG_CPU_VIEW_DISTANCE (PONG_W / 3)

#define PONG_MAX_X ((PONG_W / 2) - PONG_BALL_SIZE / 2)
#define PONG_MIN_X (-PONG_MAX_X)
#define PONG_MAX_Y ((PONG_H / 2) - PONG_BALL_SIZE / 2)
#define PONG_MIN_Y (-PONG_MAX_Y)

#define PONG_COUNTDOWN 2900
#define PONG_COUNTDOWN_FLASH_ACTIVE 700
#define PONG_SCORE_DURATION 2000
#define PONG_GAME_OVER_DURATION 5000

#define PONG_COLOR_COUNTDOWN C_YELLOW
#define PONG_COLOR_SCORE     C_WHITE
#define PONG_COLOR_WINNER    C_GREEN
#define PONG_COLOR_LOSER     C_WHITE


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

void pong_move_pad(vec_t *player, double direction, double speed);
void pong_cpu_tick(vec_t *player);
void pong_collide_pad(vec_t *player);
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
			bool show_digit = countdown >= 200 && (countdown % 1000) < PONG_COUNTDOWN_FLASH_ACTIVE;
			if (show_digit) {
				pong_draw_digit(PONG_COLOR_COUNTDOWN, (countdown / 1000) + 1, true, true);
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

		pong.p1_pos.x = -(PONG_W / 2 - 0.5);
		pong.p1_pos.y = 0;

		pong.p2_pos.x = +(PONG_W / 2 - 0.5);
		pong.p2_pos.y = 0;

		if (is_cpu && (now - pong.start) >= PONG_SERVE_DELAY) {
			const double speed_vertical_bias = 1.25;
			pong.start = now;
			pong.state = PONG_PLAYING;
			pong.ball_speed.x = is_p1 ? +1 : -1;
			pong.ball_speed.y = 2 * speed_vertical_bias * random_double() - speed_vertical_bias;
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
				pong.start = now;
				if (pong.ball_pos.x < 0) {
					pong.score_p2++;
					pong.state = pong.score_p2 < PONG_MAX_SCORE ? PONG_SCORE_P2 : PONG_GAME_OVER;
				} else {
					pong.score_p1++;
					pong.state = pong.score_p1 < PONG_MAX_SCORE ? PONG_SCORE_P1 : PONG_GAME_OVER;
				}
				break;
			}

			if (pong_reflect_value(&pong.ball_pos.y, PONG_MIN_Y, PONG_MAX_Y)) {
				pong.ball_speed.y *= -1;
			}

			if (pong.is_cpu_p1) {
				pong_cpu_tick(&pong.p1_pos);
			}
			if (pong.is_cpu_p2) {
				pong_cpu_tick(&pong.p2_pos);
			}

			pong_collide_pad(&pong.p1_pos);
			pong_collide_pad(&pong.p2_pos);
		}

		pong_draw_board();
		break;
	}

	case PONG_SCORE_P1:
	case PONG_SCORE_P2: {
		uint32_t delta = now - pong.start;
		bool is_p1 = pong.state == PONG_SCORE_P1;
		bool is_p2 = !is_p1;

		if (delta >= PONG_SCORE_DURATION) {
			pong.start = now;
			pong.state = is_p1 ? PONG_SERVE_P1 : PONG_SERVE_P2;
		} else if (delta < 250) {
			pong_draw_board();
		} else if (delta > 500) {
			bool flash = (delta / 250) % 2 == 0 || delta > (PONG_SCORE_DURATION - 500);
			bool score_p1 = (is_p1 && flash) || is_p2;
			bool score_p2 = (is_p2 && flash) || is_p1;
			pong_draw_digit(PONG_COLOR_SCORE, pong.score_p1, score_p1, false);
			pong_draw_digit(PONG_COLOR_SCORE, pong.score_p2, false, score_p2);
		}

		break;
	}

	case PONG_GAME_OVER: {
		uint32_t delta = now - pong.start;
		if (delta >= PONG_GAME_OVER_DURATION) {
			pong.start = now;
			pong.state = PONG_START;
			pong.score_p1 = pong.score_p2 = 0;
		} else if (delta > 250) {
			bool flash = (delta / 250) % 2 == 1 || delta > 1500;
			pong_draw_digit(PONG_COLOR_WINNER, pong.score_p1, flash, false);
			pong_draw_digit(PONG_COLOR_LOSER, pong.score_p2, false, flash);
		}
		break;
	}

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

void pong_move_pad(vec_t *player, double direction, double speed)
{
	const double max = (PONG_H - PONG_PAD_SIZE) / 2;
	const double min = -max;
	double pos = player->y;
	if (direction < 0) {
		pos = fmax(min, pos - speed);
	} else if (direction > 0) {
		pos = fmin(max, pos + speed);
	}
	player->y = pos;
}

bool pong_is_ball_moving_towards(vec_t *player)
{
	double ball_distance = player->x - pong.ball_pos.x;
	bool ball_is_coming = signbit(pong.ball_speed.x) == signbit(ball_distance);
	return ball_is_coming;
}

void pong_cpu_tick(vec_t *player)
{
	const double distance_margin = PONG_PAD_SIZE / 4;
	const double speed = PONG_PAD_SPEED_CPU;
	const double return_speed = speed / 6;

	double ball_distance = player->x - pong.ball_pos.x;
	bool ball_is_coming = pong_is_ball_moving_towards(player);
	ball_is_coming = ball_is_coming && fabs(ball_distance) <= PONG_CPU_VIEW_DISTANCE;

	if (ball_is_coming) {
		const double ball_offset = pong.ball_pos.y - player->y;
		if (ball_offset > distance_margin) {
			pong_move_pad(player, +1, speed);
		} else if (ball_offset < -distance_margin) {
			pong_move_pad(player, -1, speed);
		}
	} else if (PONG_CPU_RETURNS_TO_MIDDLE) {
		const double middle_offset = -player->y;
		if (middle_offset > return_speed) {
			pong_move_pad(player, +1, return_speed);
		} else if (middle_offset < -return_speed) {
			pong_move_pad(player, -1, return_speed);
		} else {
			player->y = 0;
		}
	}
}

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

void pong_collide_pad(vec_t *player)
{
	double dist = fabs(player->x - pong.ball_pos.x);
	if (dist > PONG_BALL_SIZE / 2) {
		return;
	}
	if (!pong_is_ball_moving_towards(player)) {
		return;
	}

	double offset = pong_collision_1d(player->y, PONG_PAD_SIZE, pong.ball_pos.y, PONG_BALL_SIZE);
	if (offset < EPSILON) {
		return;
	}

	if (player->x < 0) {
		pong.ball_speed.x = +fabs(pong.ball_speed.x);
	} else {
		pong.ball_speed.x = -fabs(pong.ball_speed.x);
	}
}

uint8_t pong_area_to_hsv_value(double area)
{
	return fmin(ceil(area * (double)0xFF), 0xFF);
}

void pong_draw_pad(uint8_t row, uint8_t col, vec_t xy, vec_t pad)
{
	double pad_dx = pong_collision_1d(xy.x, 1, pad.x, 1);
	double pad_dy = pong_collision_1d(xy.y, 1, pad.y, PONG_PAD_SIZE);
	double pad_area = pad_dx * pad_dy;
	if (pad_area >= EPSILON) {
		uint8_t pad_value = pong_area_to_hsv_value(pad_area);
		if (pad_value > 0) {
			HSV color = { PONG_PAD_HUE, 255, pad_value };
			led_set_by_pos_hsv(row, col, color);
		}
	}
}

void pong_draw_board(void)
{
	for (uint8_t row = 0; row < PONG_ROWS; row++) {
		for (uint8_t col = 0; col < PONG_COLS; col++) {
			double x = (double)col + 0.5 - PONG_W / 2;
			double y = (double)row + 0.5 - PONG_H / 2;
			vec_t xy = {x, y};

			double ball_area = pong_collision(pong.ball_pos, PONG_BALL_SIZE, xy, 1);
			uint8_t ball_value = pong_area_to_hsv_value(ball_area);
			if (ball_value > 0) {
				HSV color = { PONG_BALL_HUE, 255, ball_value };
				led_set_by_pos_hsv(row, col, color);
			}

			pong_draw_pad(row, col, xy, pong.p1_pos);
			pong_draw_pad(row, col, xy, pong.p2_pos);
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
