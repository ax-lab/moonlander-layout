#pragma once

enum custom_keycodes
{
	RGB_SLD = ML_SAFE_RANGE,

	S_SHIFT,
	S_CTRL,
	S_SYMBOL,
	S_NAV_L,
	S_NAV_R,
};

#define TDN(N)   TD(DANCE_ ## N)

enum tap_dance_codes
{
	DANCE_ESC,
	DANCE_PRN,
	DANCE_MAX_COUNT,
};

#define D_ESC TDN(ESC)
#define D_PRN TDN(PRN)

#define SFT_TAB  LSFT(KC_TAB)
#define ALT_TAB  LALT(KC_TAB)
#define WIN_TAB  LGUI(KC_TAB)
#define ALT_F4   LALT(KC_F4)
#define LANG_EN  LGUI(KC_KP_1)
#define LANG_JP  LGUI(KC_KP_2)

#define M_PLAY1  DYN_MACRO_PLAY1
#define M_PLAY2  DYN_MACRO_PLAY2
#define M_REC1   DYN_REC_START1
#define M_REC2   DYN_REC_START2
#define M_STOP   DYN_REC_STOP

#define ON_TOP   RCTL(RSFT(KC_UP))
#define WIN_LFT  LGUI(LSFT(KC_LEFT))
#define WIN_RGT  LGUI(LSFT(KC_RIGHT))
#define CTRL_W   LCTL(KC_W)
#define C_PGUP   LCTL(KC_PGUP)
#define C_PGDN   LCTL(KC_PGDOWN)

#define OSM_LCTL OSM(MOD_LCTL)
#define OSM_LALT OSM(MOD_LALT)
#define OSM_LGUI OSM(MOD_LGUI)

#define TL_COLOR TOGGLE_LAYER_COLOR
#define USB_PAIR WEBUSB_PAIR
#define LED_LVL  LED_LEVEL

#define ACC_A  RALT(KC_A) // ä/Ä
#define ACC_B  RALT(KC_B) // à/À
#define ACC_C  RALT(KC_C) // á/Á
#define ACC_D  RALT(KC_D) // â/Â
#define ACC_E  RALT(KC_E) // ã/Ã
#define ACC_F  RALT(KC_F) // ë/Ë
#define ACC_G  RALT(KC_G) // è/È
#define ACC_H  RALT(KC_H) // é/É
#define ACC_I  RALT(KC_I) // ê/Ê
#define ACC_J  RALT(KC_J) // ï/Ï
#define ACC_K  RALT(KC_K) // ì/Ì
#define ACC_L  RALT(KC_L) // í/Í
#define ACC_M  RALT(KC_M) // î/Î
#define ACC_N  RALT(KC_N) // ö/Ö
#define ACC_O  RALT(KC_O) // ò/Ò
#define ACC_P  RALT(KC_P) // ó/Ó
#define ACC_Q  RALT(KC_Q) // ô/Ô
#define ACC_R  RALT(KC_R) // õ/Õ
#define ACC_S  RALT(KC_S) // ü/Ü
#define ACC_T  RALT(KC_T) // ù/Ù
#define ACC_U  RALT(KC_U) // ú/Ú
#define ACC_V  RALT(KC_V) // û/Û
#define ACC_W  RALT(KC_W) // ç/Ç
#define ACC_X  RALT(KC_X) // ñ/Ñ
#define ACC_Y  RALT(KC_Y) // ß/ẞ
#define ACC_Z  RALT(KC_Z) // ¿
#define ACC_0  RALT(KC_0) // ¡
