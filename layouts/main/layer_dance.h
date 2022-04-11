#pragma once

typedef struct
{
	bool is_press_action;
	uint8_t step;
} tap;

enum
{
	SINGLE_TAP = 1,
	SINGLE_HOLD,
	DOUBLE_TAP,
	DOUBLE_HOLD,
	DOUBLE_SINGLE_TAP,
	MORE_TAPS
};

static tap dance_state[DANCE_MAX_COUNT];

uint8_t dance_step(qk_tap_dance_state_t *state);

uint8_t dance_step(qk_tap_dance_state_t *state)
{
	if (state->count == 1)
	{
		if (state->interrupted || !state->pressed)
			return SINGLE_TAP;
		else
			return SINGLE_HOLD;
	}
	else if (state->count == 2)
	{
		if (state->interrupted)
			return DOUBLE_SINGLE_TAP;
		else if (state->pressed)
			return DOUBLE_HOLD;
		else
			return DOUBLE_TAP;
	}
	return MORE_TAPS;
}

void on_dance_esc(qk_tap_dance_state_t *state, void *user_data);
void dance_esc_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_esc_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_esc(qk_tap_dance_state_t *state, void *user_data)
{
	if (state->count == 3)
	{
		tap_code16(KC_ESCAPE);
		tap_code16(KC_ESCAPE);
		tap_code16(KC_ESCAPE);
	}
	if (state->count > 3)
	{
		tap_code16(KC_ESCAPE);
	}
}

void dance_esc_finished(qk_tap_dance_state_t *state, void *user_data)
{
	dance_state[DANCE_ESC].step = dance_step(state);
	switch (dance_state[DANCE_ESC].step)
	{
	case SINGLE_TAP:
		register_code16(KC_ESCAPE);
		break;
	case SINGLE_HOLD:
		layer_on(8);
		break;
	case DOUBLE_TAP:
		register_code16(LCTL(KC_W));
		break;
	case DOUBLE_SINGLE_TAP:
		tap_code16(KC_ESCAPE);
		register_code16(KC_ESCAPE);
	}
}

void dance_esc_reset(qk_tap_dance_state_t *state, void *user_data)
{
	wait_ms(10);
	switch (dance_state[DANCE_ESC].step)
	{
	case SINGLE_TAP:
		unregister_code16(KC_ESCAPE);
		break;
	case SINGLE_HOLD:
		layer_off(8);
		break;
	case DOUBLE_TAP:
		unregister_code16(LCTL(KC_W));
		break;
	case DOUBLE_SINGLE_TAP:
		unregister_code16(KC_ESCAPE);
		break;
	}
	dance_state[DANCE_ESC].step = 0;
}

void on_dance_prn(qk_tap_dance_state_t *state, void *user_data);
void dance_prn_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_prn_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_prn(qk_tap_dance_state_t *state, void *user_data)
{
	if (state->count == 3)
	{
		tap_code16(KC_PSCREEN);
		tap_code16(KC_PSCREEN);
		tap_code16(KC_PSCREEN);
	}
	if (state->count > 3)
	{
		tap_code16(KC_PSCREEN);
	}
}

void dance_prn_finished(qk_tap_dance_state_t *state, void *user_data)
{
	dance_state[DANCE_PRN].step = dance_step(state);
	switch (dance_state[DANCE_PRN].step)
	{
	case SINGLE_TAP:
		register_code16(KC_PSCREEN);
		break;
	case SINGLE_HOLD:
		register_code16(LSFT(KC_PSCREEN));
		break;
	case DOUBLE_TAP:
		register_code16(LCTL(KC_PSCREEN));
		break;
	case DOUBLE_HOLD:
		register_code16(LCTL(LSFT(KC_PSCREEN)));
		break;
	case DOUBLE_SINGLE_TAP:
		tap_code16(KC_PSCREEN);
		register_code16(KC_PSCREEN);
	}
}

void dance_prn_reset(qk_tap_dance_state_t *state, void *user_data)
{
	wait_ms(10);
	switch (dance_state[DANCE_PRN].step)
	{
	case SINGLE_TAP:
		unregister_code16(KC_PSCREEN);
		break;
	case SINGLE_HOLD:
		unregister_code16(LSFT(KC_PSCREEN));
		break;
	case DOUBLE_TAP:
		unregister_code16(LCTL(KC_PSCREEN));
		break;
	case DOUBLE_HOLD:
		unregister_code16(LCTL(LSFT(KC_PSCREEN)));
		break;
	case DOUBLE_SINGLE_TAP:
		unregister_code16(KC_PSCREEN);
		break;
	}
	dance_state[DANCE_PRN].step = 0;
}

qk_tap_dance_action_t tap_dance_actions[DANCE_MAX_COUNT] = {
	[DANCE_ESC] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_esc, dance_esc_finished, dance_esc_reset),
	[DANCE_PRN] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_prn, dance_prn_finished, dance_prn_reset),
};
