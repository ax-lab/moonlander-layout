#pragma once

enum layer_names_t {
	LAYER_BASE = 0,
	LAYER_GAME,
	LAYER_G_TYPE,
	LAYER_MODS,
	LAYER_SYM,
	LAYER_NAV_L,
	LAYER_NAV_R,
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
#define MO_NAV_L  MO(LAYER_NAV_L)
#define MO_NAV_R  MO(LAYER_NAV_R)
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
		KC_LGUI , KC_LALT , MO_FN   , MO_NAV_L, S_SHIFT ,           MO_MOD  ,       MO_MOD  ,           S_SYMBOL, MO_NAV_R, KC_LEFT , KC_RIGHT, TG_UTIL ,
		                                        KC_ENT  , KC_TAB  , KC_SPC  ,       KC_ENT  , SFT_TAB , KC_SPC
	),
	// Game:
	[LAYER_GAME] = LAYOUT_moonlander(
		KC_ESC  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_PAUSE,       TO_BASE , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , _______ ,
		KC_TAB  , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    , KC_DEL  ,       _______ , _______ , _______ , KC_UP   , _______ , _______ , _______ ,
		KC_LSFT , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    , KC_BSPC ,       _______ , _______ , KC_LEFT , KC_DOWN , KC_RIGHT, _______ , _______ ,
		KC_LCTRL, KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    ,                           _______ , _______ , _______ , _______ , _______ , _______ ,
		KC_GRAVE, KC_LALT , _______ , MO_GMA  , KC_SPC  ,           KC_ENT  ,       TO_GTYPE,           _______ , _______ , _______ , _______ , _______ ,
		                                        MO_GMB  , KC_CAPS , _______ ,       _______ , _______ , _______
	),
	// Game typing:
	[LAYER_G_TYPE] = LAYOUT_moonlander(
		_______ , _______ , _______ , _______ , _______ , _______ , _______ ,       TO_BASE , _______ , _______ , _______ , _______ , _______ , _______ ,
		_______ , _______ , _______ , _______ , _______ , _______ , _______ ,       _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
		_______ , _______ , _______ , _______ , _______ , _______ , _______ ,       _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
		_______ , _______ , _______ , _______ , _______ , _______ ,                           _______ , _______ , _______ , _______ , _______ , _______ ,
		_______ , _______ , _______ , _______ , _______ ,           _______ ,       TO_GAME ,           _______ , _______ , _______ , _______ , _______ ,
		                                        _______ , _______ , _______ ,       _______ , _______ , _______
	),
	// Modifiers:
	[LAYER_MODS] = LAYOUT_moonlander(
		_______ , _______ , _______ , _______ , _______ , _______ , _______ ,       _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
		_______ , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , _______ ,       _______ , KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  ,
		_______ , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , _______ ,       _______ , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_F12  ,
		_______ , KC_LGUI , KC_LSFT , KC_LALT , KC_LCTRL, ALT_TAB ,                           ALT_TAB , KC_LCTRL, KC_LALT , KC_LSFT , KC_LGUI , _______ ,
		_______ , _______ , _______ , _______ , _______ ,           _______ ,       _______ ,           _______ , _______ , _______ , _______ , _______ ,
		                                        _______ , _______ , _______ ,       _______ , _______ , _______
	),
	// Symbols:
	[LAYER_SYM] = LAYOUT_moonlander(
		_______ , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , _______ ,       _______ , KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  ,
		_______ , KC_CIRC , KC_LABK , KC_AMPR , KC_RABK , _______ , _______ ,       _______ , _______ , KC_SLASH, KC_BSLS , KC_ASTR , KC_PERC , KC_F12  ,
		_______ , KC_GRAVE, KC_COLN , KC_EQUAL, KC_MINUS, KC_PLUS , LANG_JP ,       LANG_EN , KC_LBRC , KC_LPRN , KC_LCBR , KC_QUES , KC_SCLN , _______ ,
		_______ , KC_DLR  , KC_PIPE , KC_DQUO , KC_EXLM , KC_TILD ,                           KC_RBRC , KC_RPRN , KC_RCBR , KC_AT   , KC_HASH , _______ ,
		_______ , _______ , KC_F22  , KC_F20 ,  _______ ,           KC_F21  ,       _______ ,           _______ , _______ , _______ , _______ , _______ ,
		                                        _______ , M_PLAY1 , M_PLAY2 ,       _______ , _______ , _______
	),
	// Navigation:
	[LAYER_NAV_L] = LAYOUT_moonlander(
		ON_TOP  , KC_MPLY , KC_MPRV , KC_MNXT , _______ , _______ , _______ ,       _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
		WIN_LFT , WIN_RGT , _______ , KC_UP   , KC_PGUP , _______ , _______ ,       _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
		ALT_TAB , KC_HOME , KC_LEFT , KC_DOWN , KC_RIGHT, KC_END  , _______ ,       _______ , _______ , KC_LCTRL, KC_LALT , KC_LSFT , KC_LGUI , _______ ,
		_______ , _______ , KC_MINUS, KC_EQUAL, KC_PGDN , _______ ,                           _______ , KC_RCTRL, KC_RALT , KC_RSFT , KC_RGUI , _______ ,
		_______ , _______ , _______ , _______ , _______ ,           _______ ,       _______ ,           _______ , _______ , _______ , _______ , _______ ,
		                                        _______ , _______ , _______ ,       _______ , _______ , _______
	),
	[LAYER_NAV_R] = LAYOUT_moonlander(
		_______ , _______ , _______ , _______ , _______ , _______ , _______ ,       _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
		_______ , _______ , _______ , _______ , _______ , _______ , _______ ,       _______ , _______ , KC_PGUP , KC_UP   , _______ , _______ , _______ ,
		_______ , KC_LGUI , KC_LSFT , KC_LALT , KC_LCTRL, _______ , _______ ,       _______ , KC_HOME , KC_LEFT , KC_DOWN , KC_RIGHT, KC_END  , KC_F12  ,
		_______ , KC_RGUI , KC_RSFT , KC_RALT , KC_RCTRL , _______ ,                           _______ , KC_PGDN , KC_EQUAL, KC_MINUS, _______ , _______ ,
		_______ , _______ , _______ , _______ , _______ ,           _______ ,       _______ ,           _______ , _______ , _______ , _______ , _______ ,
		                                        _______ , _______ , _______ ,       _______ , _______ , _______
	),
	// Fn-keys:
	[LAYER_FN] = LAYOUT_moonlander(
		KC_PAUSE, KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F11  ,       _______ , KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  ,
		_______ , KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F12  ,       _______ , KC_F12  , KC_F7   , KC_F8   , KC_F9   , KC_F15  , KC_F12  ,
		_______ , KC_LSFT , KC_LGUI , KC_LALT , KC_LCTRL, _______ , KC_INS  ,       KC_APP  , KC_F11  , KC_F4   , KC_F5   , KC_F6   , KC_F14  , _______ ,
		_______ , _______ , _______ , _______ , _______ , _______ ,                           KC_F10  , KC_F1   , KC_F2   , KC_F3   , KC_F13  , _______ ,
		KC_CAPS , _______ , _______ , _______ , _______ ,           _______ ,       _______ ,           _______ , _______ , _______ , _______ , _______ ,
		                                        _______ , _______ , _______ ,       _______ , _______ , _______
	),
	// Accents:
	[LAYER_ACC] = LAYOUT_moonlander(
		_______ , ACC_A   , _______ , _______ , ACC_F   , ACC_J   , _______ ,       _______ , _______ , ACC_N   , _______ , ACC_S   , _______ , _______ ,
		_______ , ACC_B   , ACC_Z   , _______ , ACC_G   , ACC_K   , _______ ,       _______ , _______ , ACC_O   , _______ , ACC_T   , _______ , _______ ,
		_______ , ACC_C   , ACC_E   , ACC_W   , ACC_H   , ACC_L   , _______ ,       _______ , ACC_X   , ACC_P   , ACC_R   , ACC_U   , _______ , _______ ,
		_______ , ACC_D   , ACC_0   , ACC_Y   , ACC_I   , ACC_M   ,                           _______ , ACC_Q   , _______ , ACC_V   , _______ , _______ ,
		_______ , _______ , _______ , _______ , _______ ,           _______ ,       _______ ,           _______ , _______ , _______ , _______ , _______ ,
		                                        _______ , _______ , _______ ,       _______ , _______ , _______
	),
	// Game mod A:
	[LAYER_G_MOD_A] = LAYOUT_moonlander(
		TO_BASE , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , _______ ,       _______ , KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  ,
		_______ , KC_7    , KC_8    , KC_9    , _______ , _______ , _______ ,       _______ , _______ , _______ , _______ , _______ , _______ , KC_F12  ,
		KC_0    , KC_4    , KC_5    , KC_6    , KC_EQUAL, _______ , _______ ,       _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
		_______ , KC_1    , KC_2    , KC_3    , KC_MINUS, _______ ,                           _______ , _______ , _______ , _______ , _______ , _______ ,
		_______ , _______ , _______ , _______ , _______ ,           _______ ,       _______ ,           _______ , _______ , _______ , _______ , _______ ,
		                                        _______ , _______ , _______ ,       _______ , _______ , _______
	),
	// Game mod B:
	[LAYER_G_MOD_B] = LAYOUT_moonlander(
		_______ , _______ , _______ , _______ , _______ , _______ , _______ ,       _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
		KC_F12  , KC_F7   , KC_F8   , KC_F9   , _______ , KC_UP   , _______ ,       _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
		KC_F11  , KC_F4   , KC_F5   , KC_F6   , KC_LEFT , KC_RIGHT, _______ ,       _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
		KC_F10  , KC_F1   , KC_F2   , KC_F3   , _______ , KC_DOWN ,                           _______ , _______ , _______ , _______ , _______ , _______ ,
		_______ , _______ , _______ , _______ , _______ ,           _______ ,       _______ ,           _______ , _______ , _______ , _______ , _______ ,
		                                        _______ , _______ , _______ ,       _______ , _______ , _______
	),
	// Utilities:
	[LAYER_UTIL] = LAYOUT_moonlander(
		_______ , _______ , _______ , _______ , ALT_F4  , _______ , _______ ,       TO_BASE , _______ , _______ , _______ , _______ , USB_PAIR, RESET   ,
		_______ , _______ , CTRL_W  , C_PGUP  , C_PGDN  , _______ , _______ ,       M_PLAY1 , M_REC1  , M_STOP  , _______ , _______ , TL_COLOR, _______ ,
		_______ , _______ , _______ , _______ , _______ , _______ , D_PRN   ,       M_PLAY2 , M_REC2  , M_STOP  , _______ , _______ , LED_LVL , _______ ,
		_______ , _______ , _______ , _______ , _______ , _______ ,                           _______ , _______ , _______ , RGB_VAI , RGB_VAD , ON_TOP  ,
		_______ , _______ , KC_MUTE , KC_VOLD , KC_VOLU ,           _______ ,       WIN_TAB ,           WIN_LFT , WIN_RGT , _______ , _______ , _______ ,
		                                        KC_MPLY , KC_MNXT , KC_MPRV ,       _______ , _______ , _______
	),
	// Pad:
	[LAYER_PAD] = LAYOUT_moonlander(
		TO_GAME , _______ , _______ , _______ , _______ , _______ , _______ ,       _______ , KC_CIRC , KC_ASTR , KC_SLASH, KC_PERC , KC_LPRN , KC_RPRN ,
		ALT_TAB , KC_WH_U , KC_HOME , KC_UP   , KC_END  , KC_PGUP , _______ ,       _______ , KC_EQUAL, KC_7    , KC_8     , KC_9   , KC_EQUAL, KC_INS  ,
		KC_BSPC , KC_WH_D , KC_LEFT , KC_DOWN , KC_RIGHT, KC_PGDN , _______ ,       KC_BSPC , KC_PLUS , KC_4    , KC_5     , KC_6   , KC_UP   , KC_DEL  ,
		_______ , KC_WH_L , KC_MS_L , KC_MS_U , KC_MS_R , KC_WH_R ,                           KC_MINUS, KC_1    , KC_2     , KC_3   , KC_LEFT , KC_RIGHT,
		_______ , _______ , _______ , KC_MS_D , _______ ,           KC_BTN3 ,       SFT_TAB ,           KC_0    , KC_DOT   , KC_COMM, KC_DOWN , KC_SCLN ,
		                                        KC_BTN1 , KC_BTN2 , _______ ,       KC_SPC  , KC_TAB  , KC_ENT
	),

#if 0

	LAYOUT_moonlander(
		_______ , _______ , _______ , _______ , _______ , _______ , _______ ,       _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
		_______ , _______ , _______ , _______ , _______ , _______ , _______ ,       _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
		_______ , _______ , _______ , _______ , _______ , _______ , _______ ,       _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
		_______ , _______ , _______ , _______ , _______ , _______ ,                           _______ , _______ , _______ , _______ , _______ , _______ ,
		_______ , _______ , _______ , _______ , _______ ,           _______ ,       _______ ,           _______ , _______ , _______ , _______ , _______ ,
		                                        _______ , _______ , _______ ,       _______ , _______ , _______
	)

#endif

};
