#pragma once

enum layer_names_t {
	LAYER_BASE = 0,
	LAYER_GAME,
	LAYER_G_MOD,
	LAYER_G_TYPE,
	LAYER_MODS,
	LAYER_SYM,
	LAYER_NAV_L,
	LAYER_NAV_R,
	LAYER_FN,
	LAYER_ACC,
	LAYER_UTIL,
	LAYER_PAD,
	LAYER_MAX_COUNT,
};

#define TO_BASE   TO(LAYER_BASE)
#define TO_GAME   TO(LAYER_GAME)
#define MO_GMOD   MO(LAYER_G_MOD)
#define TO_GTYPE  TO(LAYER_G_TYPE)
#define MO_MOD    MO(LAYER_MODS)
#define MO_SYM    MO(LAYER_SYM)
#define MO_NAV_L  MO(LAYER_NAV_L)
#define MO_NAV_R  MO(LAYER_NAV_R)
#define MO_FN     MO(LAYER_FN)
#define MO_ACC    MO(LAYER_ACC)
#define TG_UTIL   TG(LAYER_UTIL)
#define TG_PAD    TG(LAYER_PAD)

const uint16_t PROGMEM keymaps[LAYER_MAX_COUNT][MATRIX_ROWS][MATRIX_COLS] = {
	//  ________, ________, ________, ________, ________, ________, ________        ________, ________, ________, ________, ________, ________, ________,

	// Base:
	[LAYER_BASE] = LAYOUT_moonlander(
		D_ESC   , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , MO_FN   ,       MO_FN   , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , TG_UTIL ,
		KC_TAB  , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    , _______ ,       TG_PAD  , KC_Y    , KC_U    , KC_I    , KC_O    , KC_MINS , KC_EQUAL,
		KC_BSPC , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    , KC_DEL  ,       KC_ESC  , KC_H    , KC_J    , KC_K    , KC_L    , KC_P    , KC_SCLN ,
		S_CTRL  , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    ,                           KC_N    , KC_M    , KC_COMMA, KC_DOT  , KC_QUOTE, KC_UP   ,
		KC_LALT , KC_LGUI , MO_FN   , MO_NAV_L, S_SHIFT ,           MO_ACC  ,       MO_ACC  ,           S_SYMBOL, MO_NAV_R, KC_LEFT , KC_RIGHT, KC_DOWN ,
		                                        KC_ENT  , KC_TAB  , KC_SPC  ,       KC_ENT  , SFT_TAB , KC_SPC
	),
	// Game:
	[LAYER_GAME] = LAYOUT_moonlander(
		KC_ESC  , _______ , _______ , _______ , _______ , _______ , KC_PAUSE,       TO_BASE , _______ , _______ , _______ , _______ , _______ , _______ ,
		KC_TAB  , _______ , _______ , _______ , _______ , _______ , _______ ,       _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
		KC_LCTRL, _______ , _______ , _______ , _______ , _______ , KC_DEL  ,       _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
		KC_LSFT , _______ , _______ , _______ , _______ , _______ ,                           _______ , _______ , _______ , _______ , _______ , _______ ,
		KC_LALT , KC_LALT , KC_GRAVE, MO_GMOD , KC_SPC  ,           KC_ENT  ,       TO_GTYPE,           _______ , _______ , _______ , _______ , _______ ,
		                                        KC_CAPS , KC_BSPC , KC_ESC  ,       _______ , _______ , _______
	),
	// Game mod:
	[LAYER_G_MOD] = LAYOUT_moonlander(
		_______ , KC_F10  , KC_F11  , KC_F12  , _______ , _______ , _______ ,       _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
		_______ , KC_F1   , KC_F2   , KC_F3   , _______ , _______ , _______ ,       _______ , _______ , KC_KP_7 , KC_KP_8 , KC_KP_9 , _______ , _______ ,
		_______ , KC_F4   , KC_F5   , KC_F6   , _______ , _______ , _______ ,       _______ , _______ , KC_KP_4 , KC_KP_5 , KC_KP_6 , _______ , _______ ,
		_______ , KC_F7   , KC_F8   , KC_F9   , _______ , _______ ,                           KC_NLCK , KC_KP_1 , KC_KP_2 , KC_KP_3 , _______ , _______ ,
		_______ , _______ , _______ , _______ , _______ ,           _______ ,       _______ ,           KC_KP_0 , _______ , _______ , _______ , _______ ,
		                                        _______ , _______ , _______ ,       _______ , _______ , _______
	),
	// Game typing:
	[LAYER_G_TYPE] = LAYOUT_moonlander(
		_______ , _______ , _______ , _______ , _______ , _______ , _______ ,       TO_BASE , _______ , _______ , _______ , _______ , _______ , _______ ,
		_______ , _______ , _______ , _______ , _______ , _______ , _______ ,       _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
		_______ , _______ , _______ , _______ , _______ , _______ , _______ ,       _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
		_______ , _______ , _______ , _______ , _______ , _______ ,                           _______ , _______ , _______ , _______ , _______ , _______ ,
		_______ , _______ , _______ , _______ , KC_LSFT ,           _______ ,       TO_GAME ,           _______ , _______ , _______ , _______ , _______ ,
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
		_______ , _______ , _______ , _______ , _______ , _______ , _______ ,       _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
		_______ , KC_TILD , KC_CIRC , KC_AMPR , KC_HASH , _______ , _______ ,       _______ , _______ , KC_LBRC , KC_RBRC , KC_PLUS , KC_MINUS, _______ ,
		_______ , KC_AT   , KC_DLR  , KC_PIPE , KC_COLN , KC_EXLM , LANG_JP ,       LANG_EN , KC_QUES , KC_LPRN , KC_RPRN , KC_GRAVE, KC_PERC , KC_MINUS,
		_______ , _______ , KC_ASTR , KC_BSLS , KC_SLASH, _______ ,                           _______ , KC_LCBR , KC_RCBR , KC_EQUAL, KC_DQUO , KC_PGUP ,
		_______ , _______ , _______ , KC_F22  , _______ ,           KC_F21  ,       _______ ,           _______ , _______ , KC_HOME , KC_END  , KC_PGDN ,
		                                        KC_F20  , M_PLAY1 , M_PLAY2 ,       _______ , _______ , _______
	),
	// Navigation:
	[LAYER_NAV_L] = LAYOUT_moonlander(
		ON_TOP  , KC_MPLY , KC_MPRV , KC_MNXT , _______ , _______ , _______ ,       _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
		WIN_LFT , WIN_RGT , ALT_TAB , KC_UP   , KC_PGUP , _______ , _______ ,       _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
		_______ , KC_HOME , KC_LEFT , KC_DOWN , KC_RIGHT, KC_END  , _______ ,       _______ , _______ , KC_LCTRL, KC_LALT , KC_LSFT , KC_LGUI , _______ ,
		_______ , _______ , KC_MINUS, KC_EQUAL, KC_PGDN , _______ ,                           _______ , KC_RCTRL, KC_RALT , KC_RSFT , KC_RGUI , _______ ,
		_______ , _______ , _______ , _______ , KC_LSFT ,           _______ ,       _______ ,           _______ , _______ , _______ , _______ , _______ ,
		                                        _______ , _______ , _______ ,       _______ , _______ , _______
	),
	[LAYER_NAV_R] = LAYOUT_moonlander(
		_______ , _______ , _______ , _______ , _______ , _______ , _______ ,       _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
		_______ , _______ , _______ , _______ , _______ , _______ , _______ ,       _______ , _______ , KC_PGUP , KC_UP   , _______ , _______ , _______ ,
		_______ , KC_LGUI , KC_LSFT , KC_LALT , KC_LCTRL, _______ , _______ ,       _______ , KC_HOME , KC_LEFT , KC_DOWN , KC_RIGHT, KC_END  , KC_F12  ,
		_______ , KC_RGUI , KC_RSFT , KC_RALT , KC_RCTRL, _______ ,                           _______ , KC_PGDN , KC_EQUAL, KC_MINUS, _______ , _______ ,
		_______ , _______ , _______ , _______ , KC_LSFT ,           _______ ,       _______ ,           _______ , _______ , _______ , _______ , _______ ,
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
		_______ , ACC_AD  , _______ , _______ , ACC_ED  , ACC_ID  , _______ ,       _______ , _______ , ACC_OD  , _______ , ACC_UD  , _______ , _______ ,
		_______ , ACC_AG  , ACC_XQ  , _______ , ACC_EG  , ACC_IG  , _______ ,       _______ , _______ , ACC_OG  , _______ , ACC_UG  , _______ , _______ ,
		_______ , ACC_AA  , ACC_AT  , ACC_CC  , ACC_EA  , ACC_IA  , _______ ,       _______ , ACC_NT  , ACC_OA  , ACC_OT  , ACC_UA  , _______ , _______ ,
		_______ , ACC_AC  , ACC_XE  , ACC_SS  , ACC_EC  , ACC_IC  ,                           _______ , ACC_OC  , _______ , ACC_UC  , _______ , _______ ,
		_______ , _______ , _______ , _______ , KC_LSFT ,           _______ ,       _______ ,           _______ , _______ , _______ , _______ , _______ ,
		                                        _______ , _______ , _______ ,       _______ , _______ , _______
	),
	// Utilities:
	[LAYER_UTIL] = LAYOUT_moonlander(
		TO_GAME , _______ , _______ , _______ , ALT_F4  , _______ , _______ ,       TO_BASE , _______ , _______ , _______ , _______ , USB_PAIR, _______ ,
		_______ , _______ , CTRL_W  , C_PGUP  , C_PGDN  , _______ , _______ ,       M_PLAY1 , M_REC1  , M_STOP  , _______ , _______ , TL_COLOR, _______ ,
		_______ , _______ , _______ , _______ , _______ , _______ , D_PRN   ,       M_PLAY2 , M_REC2  , M_STOP  , _______ , _______ , LED_LVL , _______ ,
		_______ , _______ , _______ , _______ , _______ , _______ ,                           _______ , _______ , _______ , RGB_VAI , RGB_VAD , _______ ,
		_______ , _______ , KC_MUTE , KC_VOLD , KC_VOLU ,           _______ ,       _______ ,           _______ , _______ , _______ , _______ , RESET   ,
		                                        KC_MPLY , KC_MNXT , KC_MPRV ,       _______ , _______ , _______
	),
	// Pad:
	[LAYER_PAD] = LAYOUT_moonlander(
		_______ , _______ , _______ , _______ , _______ , _______ , _______ ,       KC_ESC  , KC_CIRC , KC_KP_7 , KC_KP_8 , KC_KP_9 , KC_EQUAL, KC_INS  ,
		_______ , _______ , _______ , _______ , _______ , _______ , _______ ,       _______ , KC_ASTR , KC_KP_4 , KC_KP_5 , KC_KP_6 , KC_PMNS , KC_PPLS ,
		_______ , _______ , _______ , _______ , _______ , _______ , _______ ,       KC_BSPC , KC_SLASH, KC_KP_1 , KC_KP_2 , KC_KP_3 , KC_PERC , KC_DEL  ,
		_______ , _______ , _______ , _______ , _______ , _______ ,                           KC_NLCK , KC_KP_0 , KC_COMMA, KC_DOT  , _______ , KC_UP   ,
		KC_RALT , _______ , _______ , _______ , _______ ,           _______ ,       SFT_TAB ,           KC_LPRN , KC_RPRN , KC_LEFT , KC_RIGHT, KC_DOWN ,
		                                        _______ , _______ , _______ ,       KC_PENT , KC_TAB  , _______
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
