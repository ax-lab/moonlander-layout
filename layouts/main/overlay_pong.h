#pragma once

#define PONG_CONTROL_P1_ROW 5
#define PONG_CONTROL_P2_ROW 11

#define PONG_CONTROL_P1_UP    0
#define PONG_CONTROL_P1_DOWN  1
#define PONG_CONTROL_P1_SERVE 2

#define PONG_CONTROL_P2_UP    6
#define PONG_CONTROL_P2_DOWN  5
#define PONG_CONTROL_P2_SERVE 4

#define PONG_CONTROL_QUIT  3

#define PONG_CONTROL_COLOR C_PINK

#define PONG_TICK 10
#define PONG_ROWS (LAYOUT_ROWS - 1)
#define PONG_COLS (LAYOUT_COLS)
#define PONG_W ((double)PONG_COLS)
#define PONG_H ((double)PONG_ROWS)

#define PONG_MAX_SCORE 3

#define PONG_BALL_SIZE      1.0
#define PONG_BALL_HUE       85
#define PONG_BALL_SPEED     0.06
#define PONG_BALL_SPEED_MAX 0.20
#define PONG_BALL_ACCELERATION 1.09

#define PONG_PAD_SIZE 1.5
#define PONG_PAD_HUE  201
#define PONG_PAD_SPEED_PLAYER 0.03
#define PONG_PAD_SPEED_CPU    0.02
#define PONG_PAD_ALIGN_GRID   false

#define PONG_PAD_ANGLE (M_PI / 8)

#define PONG_SERVE_DELAY 500
#define PONG_CPU_RETURNS_TO_MIDDLE false
#define PONG_CPU_VIEW_DISTANCE (PONG_W / 3)

#define PONG_MAX_X ((PONG_W / 2) - PONG_BALL_SIZE / 2)
#define PONG_MIN_X (-PONG_MAX_X)
#define PONG_MAX_Y ((PONG_H / 2) - PONG_BALL_SIZE / 2)
#define PONG_MIN_Y (-PONG_MAX_Y)

#define PONG_COUNTDOWN 2900
#define PONG_COUNTDOWN_FLASH_ACTIVE 1000
#define PONG_SCORE_DURATION 2000
#define PONG_GAME_OVER_DURATION 5000

#define PONG_COLOR_COUNTDOWN C_YELLOW
#define PONG_COLOR_SCORE     C_WHITE
#define PONG_COLOR_WINNER    C_GREEN
#define PONG_COLOR_LOSER     C_WHITE

static bool pong_sound_muted = false;

float pong_sound_hit_bat[][2]  = SONG(Q__NOTE(_C6));
float pong_sound_hit_wall[][2] = SONG(Q__NOTE(_A2));
float pong_sound_point[][2]    = SONG(H__NOTE(_A4), H__NOTE(_B4));
float pong_sound_win[][2]      = SONG(
	E__NOTE(_A5), E__NOTE(_B5), E__NOTE(_CS6), E__NOTE(_D6), E__NOTE(_E6), E__NOTE(_FS6), E__NOTE(_GS6), E__NOTE(_A6));

#define PONG_PLAY(name) (!pong_sound_muted ? PLAY_SONG(pong_sound_ ## name) : (void)0)

typedef enum {
	PONG_START,
	PONG_SERVE_P1,
	PONG_SERVE_P2,
	PONG_PLAYING,
	PONG_SCORE_P1,
	PONG_SCORE_P2,
	PONG_GAME_OVER,
} pong_state_t;

typedef struct {
	bool up;
	bool down;
	bool serve;
} pong_controls_t;

static struct {
	vec_t ball_pos;
	vec_t ball_speed;
	vec_t p1_pos;
	vec_t p2_pos;

	uint32_t start;
	uint32_t input_timer;

	uint8_t score_p1;
	uint8_t score_p2;

	pong_state_t state;

	bool is_cpu_p1;
	bool is_cpu_p2;

	pong_controls_t controls_p1;
	pong_controls_t controls_p2;
} pong = { 0 };

void pong_move_pad(vec_t *player, double direction, double speed);
void pong_cpu_tick(vec_t *player);
void pong_collide_pad(vec_t *player);
bool pong_reflect_value(double *v, double min, double max);
void pong_draw_board(void);
void pong_draw_digit(HSV color, int digit, bool p1, bool p2);

bool pong_overlay_process(uint16_t keycode, keyrecord_t *record)
{
	uint8_t col = record->event.key.col;
	uint8_t row = record->event.key.row;

	if (keycode == KC_M) {
		if (record->event.pressed) {
			pong_sound_muted = !pong_sound_muted;
		}
		return false;
	}

	bool *player_is_cpu_flag = 0;
	pong_controls_t *controls = 0;
	if (row == PONG_CONTROL_P1_ROW) {
		player_is_cpu_flag = &pong.is_cpu_p1;
		controls = &pong.controls_p1;
	} else if (row == PONG_CONTROL_P2_ROW) {
		player_is_cpu_flag = &pong.is_cpu_p2;
		controls = &pong.controls_p2;
	}

	if (player_is_cpu_flag) {
		bool is_cpu = *player_is_cpu_flag;
		bool pressed = record->event.pressed;
		switch (col) {
			case PONG_CONTROL_P1_UP:
			case PONG_CONTROL_P2_UP:
				is_cpu = false;
				controls->up = pressed;
				break;
			case PONG_CONTROL_P1_DOWN:
			case PONG_CONTROL_P2_DOWN:
				is_cpu = false;
				controls->down = pressed;
				break;
			case PONG_CONTROL_P1_SERVE:
			case PONG_CONTROL_P2_SERVE:
				is_cpu = false;
				controls->serve = pressed;
				break;
			case PONG_CONTROL_QUIT:
				is_cpu = true;
				break;
		}
		*player_is_cpu_flag = is_cpu;
	} else {
		close_overlay();
	}

	return false;
}

void pong_overlay_rgb(void)
{
	clear_led_matrix();

	uint32_t now = timer_read32();

	bool enable_input_flash = false;
	uint8_t flash_controls_fade = 0;

	uint32_t delay = now - pong.start;
	const double ramp_up = 0.25;
	const double time_on = 0.50;
	const double time_dn = 0.10;
	const uint32_t phase_time = 500;
	double phase = (double)(delay % phase_time) / phase_time;
	double flash = 0;
	if (phase <= ramp_up) {
		flash = phase / ramp_up;
	} else if (phase <= ramp_up + time_on) {
		flash = 1;
	} else if (phase <= ramp_up + time_on + time_dn) {
		double pos = phase - ramp_up - time_on;
		flash = (time_dn - pos) / time_dn;
	}
	if (flash > EPSILON) {
		flash_controls_fade = fmin(ceil(flash * 0xFF), 0xFF);
	}

	if (pong.input_timer == 0 || now - pong.input_timer > PONG_TICK * 5) {
		pong.input_timer = now;
	}

	while (now - pong.input_timer > PONG_TICK) {
		pong.input_timer += PONG_TICK;
		if (pong.state != PONG_PLAYING && pong.state != PONG_SERVE_P1 && pong.state != PONG_SERVE_P2) {
			continue;
		}
		if (!pong.is_cpu_p1) {
			if (pong.controls_p1.up) {
				pong_move_pad(&pong.p1_pos, -1, PONG_PAD_SPEED_PLAYER);
			}
			if (pong.controls_p1.down) {
				pong_move_pad(&pong.p1_pos, +1, PONG_PAD_SPEED_PLAYER);
			}
		}
		if (!pong.is_cpu_p2) {
			if (pong.controls_p2.up) {
				pong_move_pad(&pong.p2_pos, -1, PONG_PAD_SPEED_PLAYER);
			}
			if (pong.controls_p2.down) {
				pong_move_pad(&pong.p2_pos, +1, PONG_PAD_SPEED_PLAYER);
			}
		}
	}

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
			enable_input_flash = true;
		}
		break;
	}

	case PONG_SERVE_P1:
	case PONG_SERVE_P2: {
		uint32_t delay = now - pong.start;

		bool is_p1 = pong.state == PONG_SERVE_P1;
		bool is_p2 = !is_p1;
		bool is_cpu = (is_p1 && pong.is_cpu_p1) || (is_p2 && pong.is_cpu_p2);

		pong.ball_pos.y = 0;
		pong.ball_pos.x = ((PONG_W / 2) - 1.5) * (is_p1 ? -1 : +1);
		pong.ball_speed = vec_zero();

		if (delay < 100) {
			pong.p1_pos.x = -(PONG_W / 2 - 0.5);
			pong.p1_pos.y = 0;
			pong.p2_pos.x = +(PONG_W / 2 - 0.5);
			pong.p2_pos.y = 0;
		}

		bool serve = is_cpu && delay >= PONG_SERVE_DELAY;
		serve = serve || (!is_cpu && is_p1 && pong.controls_p1.serve);
		serve = serve || (!is_cpu && is_p2 && pong.controls_p2.serve);

		if (serve) {
			pong.start = now;
			pong.state = PONG_PLAYING;
			pong.ball_speed.x = is_p1 ? +1 : -1;

			const double speed_vertical_bias = 1.25;
			double vertical;
			if (is_cpu) {
				vertical = random_double() - 0.5;
			} else {
				double pos_y = is_p1 ? pong.p1_pos.y : pong.p2_pos.y;
				vertical = -pos_y / PONG_H;
			}

			pong.ball_speed.y = 2 * speed_vertical_bias * vertical;
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
				if (pong.state == PONG_GAME_OVER) {
					PONG_PLAY(win);
				} else {
					PONG_PLAY(point);
				}
				break;
			}

			if (pong_reflect_value(&pong.ball_pos.y, PONG_MIN_Y, PONG_MAX_Y)) {
				pong.ball_speed.y *= -1;
				PONG_PLAY(hit_wall);
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
			bool p1_win = pong.score_p1 > pong.score_p2;
			bool flash = (delta / 250) % 2 == 1 || delta > 1500;
			HSV p1 = p1_win ? PONG_COLOR_WINNER : PONG_COLOR_LOSER;
			HSV p2 = p1_win ? PONG_COLOR_LOSER : PONG_COLOR_WINNER;
			pong_draw_digit(p1, pong.score_p1, flash, false);
			pong_draw_digit(p2, pong.score_p2, false, flash);
		}
		break;
	}

	}

	if (!pong.is_cpu_p1 || enable_input_flash) {
		HSV c_keys = PONG_CONTROL_COLOR;
		HSV c_quit = C_RED;
		if (pong.is_cpu_p1) {
			c_keys.v = flash_controls_fade;
			c_quit.v = 0;
		}
		HSV c_serve = c_keys;
		if (pong.state == PONG_SERVE_P1) {
			c_serve.v = flash_controls_fade;
		}
		uint8_t row = PONG_CONTROL_P1_ROW;
		led_set_by_row_col_hsv(row, PONG_CONTROL_P1_UP, c_keys);
		led_set_by_row_col_hsv(row, PONG_CONTROL_P1_DOWN, c_keys);
		led_set_by_row_col_hsv(row, PONG_CONTROL_P1_SERVE, c_serve);
		led_set_by_row_col_hsv(row, PONG_CONTROL_QUIT, c_quit);
	}

	if (!pong.is_cpu_p2 || enable_input_flash) {
		HSV c_keys = PONG_CONTROL_COLOR;
		HSV c_quit = C_RED;
		if (pong.is_cpu_p2) {
			c_keys.v = flash_controls_fade;
			c_quit.v = 0;
		}
		HSV c_serve = c_keys;
		if (pong.state == PONG_SERVE_P2) {
			c_serve.v = flash_controls_fade;
		}
		uint8_t row = PONG_CONTROL_P2_ROW;
		led_set_by_row_col_hsv(row, PONG_CONTROL_P2_UP, c_keys);
		led_set_by_row_col_hsv(row, PONG_CONTROL_P2_DOWN, c_keys);
		led_set_by_row_col_hsv(row, PONG_CONTROL_P2_SERVE, c_serve);
		led_set_by_row_col_hsv(row, PONG_CONTROL_QUIT, c_quit);
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
	bool is_p1 = player->x < 0;

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

	PONG_PLAY(hit_bat);

	double current_speed = vec_len(pong.ball_speed);
	double collision_delta = (pong.ball_pos.y - player->y) / PONG_PAD_SIZE;

	double collision_angle = PONG_PAD_ANGLE * collision_delta;
	vec_t collision_normal = { cos(collision_angle), sin(collision_angle) };
	if (!is_p1) {
		collision_normal.x *= -1;
	}

	vec_t inbound = vec_norm(pong.ball_speed);
	vec_t reflected = vec_add(inbound, vec_scale(collision_normal, -2 * vec_dot_prod(inbound, collision_normal)));

	vec_t reflected_speed = vec_scale(vec_norm(reflected), current_speed);

	// accelerating only on the horizontal axis counteracts any vertical
	// tendency acquired by the ball, at the cost of a somewhat random
	// change in speed
	reflected_speed.x *= PONG_BALL_ACCELERATION;

	// we want to avoid generating vertical speeds, which can easily happen
	// if the pad arc angle is big, but can still happen even with lesser
	// angles
	const double min_horizontal_component = 0.05;
	if (is_p1) {
		reflected_speed.x = fmax(reflected_speed.x, +min_horizontal_component);
	} else {
		reflected_speed.x = fmin(reflected_speed.x, -min_horizontal_component);
	}

	double new_speed = vec_len(reflected_speed);
	if (new_speed > PONG_BALL_SPEED_MAX) {
		reflected_speed = vec_scale(vec_norm(reflected_speed), PONG_BALL_SPEED_MAX);
	}

	pong.ball_speed = reflected_speed;
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
