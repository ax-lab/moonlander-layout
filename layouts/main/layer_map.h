#pragma once

enum layer_names_t {
	LAYER_BASE = 0,
	LAYER_GAME,
	LAYER_G_TYPE,
	LAYER_MODS,
	LAYER_SYM,
	LAYER_NUM,
	LAYER_NAV,
	LAYER_FN,
	LAYER_ACC,
	LAYER_G_MOD_A,
	LAYER_G_MOD_B,
	LAYER_UTIL,
	LAYER_PAD,
	LAYER_MAX_COUNT,
};

#define TO_BASE   TO(LAYER_BASE)
#define TO_GAME   TO(LAYER_GAME)
#define TO_GTYPE  TO(LAYER_G_TYPE)
#define MO_MOD    MO(LAYER_MODS)
#define MO_SYM    MO(LAYER_SYM)
#define MO_NUM    MO(LAYER_NUM)
#define MO_NAV    MO(LAYER_NAV)
#define MO_FN     MO(LAYER_FN)
#define MO_ACC    MO(LAYER_ACC)
#define MO_GMA    MO(LAYER_G_MOD_A)
#define MO_GMB    MO(LAYER_G_MOD_B)
#define TG_UTIL   TG(LAYER_UTIL)
#define TG_PAD    TG(LAYER_PAD)

const uint16_t PROGMEM keymaps[LAYER_MAX_COUNT][MATRIX_ROWS][MATRIX_COLS] = {
	//  ________, ________, ________, ________, ________, ________, ________        ________, ________, ________, ________, ________, ________, ________,

	// Base:
	[LAYER_BASE] = LAYOUT_moonlander(
		D_ESC   , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , MO_FN   ,       MO_FN   , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_UP   ,
		KC_TAB  , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    , TG_PAD  ,       TG_PAD  , KC_Y    , KC_U    , KC_I    , KC_O    , KC_UNDS , KC_DOWN ,
		KC_BSPC , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    , KC_DEL  ,       KC_ESC  , KC_H    , KC_J    , KC_K    , KC_L    , KC_P    , MO_ACC  ,
		S_CTRL  , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    ,                           KC_N    , KC_M    , KC_COMMA, KC_DOT  , KC_QUOTE, KC_LCTRL,
		KC_LGUI , KC_LALT , MO_FN   , MO_NAV  , S_SHIFT ,           MO_MOD  ,       MO_MOD  ,           S_SYMBOL, MO_NUM  , KC_LEFT , KC_RIGHT, TG_UTIL ,
		                                        KC_ENT  , KC_TAB  , KC_SPC  ,       KC_ENT  , SFT_TAB , KC_SPC
	),
	// Game:
	[LAYER_GAME] = LAYOUT_moonlander(
		KC_ESC  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_PAUSE,       TO_BASE , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_TRNS ,
		KC_TAB  , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    , KC_DEL  ,       KC_TRNS , KC_TRNS , KC_TRNS , KC_UP   , KC_TRNS , KC_TRNS , KC_TRNS ,
		KC_LSFT , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    , KC_BSPC ,       KC_TRNS , KC_TRNS , KC_LEFT , KC_DOWN , KC_RIGHT, KC_TRNS , KC_TRNS ,
		KC_LCTRL, KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    ,                           KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		KC_GRAVE, KC_LALT , KC_TRNS , MO_GMA  , KC_SPC  ,           KC_ENT  ,       TO_GTYPE,           KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		                                        MO_GMB  , KC_CAPS , KC_TRNS ,       KC_TRNS , KC_TRNS , KC_TRNS
	),
	// Game typing:
	[LAYER_G_TYPE] = LAYOUT_moonlander(
		KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,       TO_BASE , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,       KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,       KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                           KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,           KC_TRNS ,       TO_GAME ,           KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		                                        KC_TRNS , KC_TRNS , KC_TRNS ,       KC_TRNS , KC_TRNS , KC_TRNS
	),
	// Modifiers:
	[LAYER_MODS] = LAYOUT_moonlander(
		KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,       KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		KC_TRNS , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_TRNS ,       KC_TRNS , KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  ,
		KC_TRNS , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_TRNS ,       KC_TRNS , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_F12  ,
		KC_TRNS , KC_LGUI , KC_LSFT , KC_LALT , KC_LCTRL, ALT_TAB ,                           ALT_TAB , KC_RCTRL, KC_RALT , KC_RSFT , KC_RGUI , KC_TRNS ,
		KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,           KC_TRNS ,       KC_TRNS ,           KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		                                        KC_TRNS , KC_TRNS , KC_TRNS ,       KC_TRNS , KC_TRNS , KC_TRNS
	),
	// Symbols:
	[LAYER_SYM] = LAYOUT_moonlander(
		KC_TRNS , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_TRNS ,       KC_TRNS , KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  ,
		KC_TRNS , KC_CIRC , KC_LABK , KC_AMPR , KC_RABK , KC_TRNS , KC_TRNS ,       KC_TRNS , KC_TRNS , KC_SLASH, KC_BSLS , KC_ASTR , KC_PERC , KC_F12  ,
		KC_TRNS , KC_GRAVE, KC_COLN , KC_EQUAL, KC_MINUS, KC_PLUS , LANG_JP ,       LANG_EN , KC_LBRC , KC_LPRN , KC_LCBR , KC_QUES , KC_SCLN , KC_TRNS ,
		KC_TRNS , KC_DLR  , KC_PIPE , KC_DQUO , KC_EXLM , KC_TILD ,                           KC_RBRC , KC_RPRN , KC_RCBR , KC_AT   , KC_HASH , KC_TRNS ,
		KC_TRNS , KC_TRNS , KC_F22  , KC_F20 ,  KC_TRNS ,           KC_F21  ,       KC_TRNS ,           KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		                                        KC_TRNS , M_PLAY1 , M_PLAY2 ,       KC_TRNS , KC_TRNS , KC_TRNS
	),
	// Numeric:
	[LAYER_NUM] = LAYOUT_moonlander(
		KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,       KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		KC_NLCK , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_SLCK ,       KC_TRNS , KC_TRNS , KC_SLASH, KC_TRNS , KC_ASTR , KC_PERC , KC_TRNS ,
		KC_TRNS , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_TRNS ,       KC_TRNS , KC_TRNS , KC_7    , KC_8    , KC_9    , KC_0    , KC_TRNS ,
		KC_TRNS , KC_DLR  , KC_TRNS , KC_MINUS, KC_EQUAL, KC_TRNS ,                           KC_TRNS , KC_6    , KC_TRNS , KC_TRNS , KC_HASH , KC_TRNS ,
		KC_TRNS , KC_TRNS , KC_TRNS , KC_RALT , KC_TRNS ,           KC_TRNS ,       KC_TRNS ,           KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		                                        KC_TRNS , KC_TRNS , KC_TRNS ,       KC_TRNS , KC_TRNS , KC_TRNS
	),
	// Navigation:
	[LAYER_NAV] = LAYOUT_moonlander(
		ON_TOP  , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,       KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		WIN_LFT , WIN_RGT , KC_PGUP , KC_UP   , KC_F12  , KC_TRNS , KC_TRNS ,       KC_TRNS , KC_TRNS , KC_MPLY , KC_MNXT , KC_MPRV , KC_TRNS , KC_TRNS ,
		KC_TRNS , KC_HOME , KC_LEFT , KC_DOWN , KC_RIGHT, KC_END  , KC_TRNS ,       KC_TRNS , KC_TRNS , KC_LCTRL, KC_LALT , KC_LGUI , KC_LSFT , KC_TRNS ,
		ALT_TAB , KC_TRNS , KC_PGDN , KC_MINUS, KC_EQUAL, KC_TRNS ,                           KC_TRNS , WIN_LFT , WIN_RGT , KC_TRNS , KC_TRNS , KC_TRNS ,
		WIN_TAB , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,           KC_TRNS ,       KC_TRNS ,           KC_LSFT , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		                                        KC_TRNS , KC_TRNS , KC_TRNS ,       KC_TRNS , KC_TRNS , KC_TRNS
	),
	// Fn-keys:
	[LAYER_FN] = LAYOUT_moonlander(
		KC_PAUSE, KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F11  ,       KC_TRNS , KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  ,
		KC_TRNS , KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F12  ,       KC_TRNS , KC_F12  , KC_F7   , KC_F8   , KC_F9   , KC_F15  , KC_F12  ,
		KC_TRNS , KC_LSFT , KC_LGUI , KC_LALT , KC_LCTRL, KC_TRNS , KC_INS  ,       KC_APP  , KC_F11  , KC_F4   , KC_F5   , KC_F6   , KC_F14  , KC_TRNS ,
		KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                           KC_F10  , KC_F1   , KC_F2   , KC_F3   , KC_F13  , KC_TRNS ,
		KC_CAPS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,           KC_TRNS ,       KC_TRNS ,           KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		                                        KC_TRNS , KC_TRNS , KC_TRNS ,       KC_TRNS , KC_TRNS , KC_TRNS
	),
	// Accents:
	[LAYER_ACC] = LAYOUT_moonlander(
		KC_TRNS , ACC_A   , KC_TRNS , KC_TRNS , ACC_F   , ACC_J   , KC_TRNS ,       KC_TRNS , KC_TRNS , ACC_N   , KC_TRNS , ACC_S   , KC_TRNS , KC_TRNS ,
		KC_TRNS , ACC_B   , ACC_Z   , KC_TRNS , ACC_G   , ACC_K   , KC_TRNS ,       KC_TRNS , KC_TRNS , ACC_O   , KC_TRNS , ACC_T   , KC_TRNS , KC_TRNS ,
		KC_TRNS , ACC_C   , ACC_E   , ACC_W   , ACC_H   , ACC_L   , KC_TRNS ,       KC_TRNS , ACC_X   , ACC_P   , ACC_R   , ACC_U   , KC_TRNS , KC_TRNS ,
		KC_TRNS , ACC_D   , ACC_0   , ACC_Y   , ACC_I   , ACC_M   ,                           KC_TRNS , ACC_Q   , KC_TRNS , ACC_V   , KC_TRNS , KC_TRNS ,
		KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,           KC_TRNS ,       KC_TRNS ,           KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		                                        KC_TRNS , KC_TRNS , KC_TRNS ,       KC_TRNS , KC_TRNS , KC_TRNS
	),
	// Game mod A:
	[LAYER_G_MOD_A] = LAYOUT_moonlander(
		TO_BASE , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_TRNS ,       KC_TRNS , KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  ,
		KC_TRNS , KC_7    , KC_8    , KC_9    , KC_TRNS , KC_TRNS , KC_TRNS ,       KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_F12  ,
		KC_0    , KC_4    , KC_5    , KC_6    , KC_EQUAL, KC_TRNS , KC_TRNS ,       KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		KC_TRNS , KC_1    , KC_2    , KC_3    , KC_MINUS, KC_TRNS ,                           KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,           KC_TRNS ,       KC_TRNS ,           KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		                                        KC_TRNS , KC_TRNS , KC_TRNS ,       KC_TRNS , KC_TRNS , KC_TRNS
	),
	// Game mod B:
	[LAYER_G_MOD_B] = LAYOUT_moonlander(
		KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,       KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		KC_F12  , KC_F7   , KC_F8   , KC_F9   , KC_TRNS , KC_UP   , KC_TRNS ,       KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		KC_F11  , KC_F4   , KC_F5   , KC_F6   , KC_LEFT , KC_RIGHT, KC_TRNS ,       KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		KC_F10  , KC_F1   , KC_F2   , KC_F3   , KC_TRNS , KC_DOWN ,                           KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,           KC_TRNS ,       KC_TRNS ,           KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		                                        KC_TRNS , KC_TRNS , KC_TRNS ,       KC_TRNS , KC_TRNS , KC_TRNS
	),
	// Utilities:
	[LAYER_UTIL] = LAYOUT_moonlander(
		KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , ALT_F4  , KC_TRNS , KC_TRNS ,       TO_BASE , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , USB_PAIR, RESET   ,
		KC_TRNS , KC_TRNS , CTRL_W  , C_PGUP  , C_PGDN  , KC_TRNS , KC_TRNS ,       M_PLAY1 , M_REC1  , M_STOP  , KC_TRNS , KC_TRNS , TL_COLOR, KC_TRNS ,
		KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , D_PRN   ,       M_PLAY2 , M_REC2  , M_STOP  , KC_TRNS , KC_TRNS , LED_LVL , KC_TRNS ,
		KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                           KC_TRNS , KC_TRNS , KC_TRNS , RGB_VAI , RGB_VAD , ON_TOP  ,
		KC_TRNS , KC_TRNS , KC_MUTE , KC_VOLD , KC_VOLU ,           KC_TRNS ,       WIN_TAB ,           WIN_LFT , WIN_RGT , KC_TRNS , KC_TRNS , KC_TRNS ,
		                                        KC_MPLY , KC_MNXT , KC_MPRV ,       KC_TRNS , KC_TRNS , KC_TRNS
	),
	// Pad:
	[LAYER_PAD] = LAYOUT_moonlander(
		TO_GAME , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,       KC_TRNS , KC_CIRC , KC_ASTR , KC_SLASH, KC_PERC , KC_LPRN , KC_RPRN ,
		ALT_TAB , KC_WH_U , KC_HOME , KC_UP   , KC_END  , KC_PGUP , KC_TRNS ,       KC_TRNS , KC_EQUAL, KC_7    , KC_8     , KC_9   , KC_EQUAL, KC_INS  ,
		KC_BSPC , KC_WH_D , KC_LEFT , KC_DOWN , KC_RIGHT, KC_PGDN , KC_TRNS ,       KC_BSPC , KC_PLUS , KC_4    , KC_5     , KC_6   , KC_UP   , KC_DEL  ,
		KC_TRNS , KC_WH_L , KC_MS_L , KC_MS_U , KC_MS_R , KC_WH_R ,                           KC_MINUS, KC_1    , KC_2     , KC_3   , KC_LEFT , KC_RIGHT,
		KC_TRNS , KC_TRNS , KC_TRNS , KC_MS_D , KC_TRNS ,           KC_BTN3 ,       SFT_TAB ,           KC_0    , KC_DOT   , KC_COMM, KC_DOWN , KC_SCLN ,
		                                        KC_BTN1 , KC_BTN2 , KC_TRNS ,       KC_SPC  , KC_TAB  , KC_ENT
	),

#if 0

	LAYOUT_moonlander(
		KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,       KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,       KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,       KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                           KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,           KC_TRNS ,       KC_TRNS ,           KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		                                        KC_TRNS , KC_TRNS , KC_TRNS ,       KC_TRNS , KC_TRNS , KC_TRNS
	)

#endif

};
