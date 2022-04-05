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

// Accent aliases (a = acute, g = grave, t = tilde, c = circumflex, d = diaeresis)

#define ACC_AD ACC_A // ä/Ä  A-diaeresis
#define ACC_AG ACC_B // à/À  A-grave
#define ACC_AA ACC_C // á/Á  A-acute
#define ACC_AC ACC_D // â/Â  A-circumflex
#define ACC_AT ACC_E // ã/Ã  A-tilde
#define ACC_ED ACC_F // ë/Ë  E-diaeresis
#define ACC_EG ACC_G // è/È  E-grave
#define ACC_EA ACC_H // é/É  E-acute
#define ACC_EC ACC_I // ê/Ê  E-circumflex
#define ACC_ID ACC_J // ï/Ï  I-diaeresis
#define ACC_IG ACC_K // ì/Ì  I-grave
#define ACC_IA ACC_L // í/Í  I-acute
#define ACC_IC ACC_M // î/Î  I-circumflex
#define ACC_OD ACC_N // ö/Ö  O-diaeresis
#define ACC_OG ACC_O // ò/Ò  O-grave
#define ACC_OA ACC_P // ó/Ó  O-acute
#define ACC_OC ACC_Q // ô/Ô  O-circumflex
#define ACC_OT ACC_R // õ/Õ  O-tilde
#define ACC_UD ACC_S // ü/Ü  U-diaeresis
#define ACC_UG ACC_T // ù/Ù  U-grave
#define ACC_UA ACC_U // ú/Ú  U-acute
#define ACC_UC ACC_V // û/Û  U-circumflex
#define ACC_CC ACC_W // ç/Ç  C-cedilla
#define ACC_NT ACC_X // ñ/Ñ  N-tilde
#define ACC_SS ACC_Y // ß/ẞ  Eszett (ss)
#define ACC_IQ ACC_Z // ¿    Inverted question mark
#define ACC_IE ACC_0 // ¡    Inverted exclamation mark
