#include "moonlander.h"
#include "version.h"

#ifdef CONSOLE_ENABLE
	#define ENABLE_OUTPUT 1
#else
	#define ENABLE_OUTPUT 0
#endif

#if ENABLE_OUTPUT
	#include "print.h"
	#define output uprintf
#else
	#define output(...) (void)0
#endif

#include "util.h"

#include "leds.h"
#include "overlay.h"

#include "overlay_pong.h"
#include "overlay_rainbow.h"
#include "overlay_simple_snake.h"
#include "overlay_menu.h"

enum custom_keycodes
{
	RGB_SLD = ML_SAFE_RANGE,
};

#define TDN(N)   TD(DANCE_ ## N)

enum tap_dance_codes
{
	DANCE_0,
	DANCE_1,
};

#define D_ESC TDN(0)
#define D_PRN TDN(1)

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

#define LAYER_BASE      0
#define LAYER_GAME      1
#define LAYER_G_TYPE    2
#define LAYER_MODS      3
#define LAYER_SYM       4
#define LAYER_NUM       5
#define LAYER_NAV       6
#define LAYER_FN        7
#define LAYER_ACC       8
#define LAYER_G_MOD_A   9
#define LAYER_G_MOD_B   10
#define LAYER_UTIL      11
#define LAYER_PAD       12

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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	//  ________, ________, ________, ________, ________, ________, ________        ________, ________, ________, ________, ________, ________, ________,

	// Base:
	[LAYER_BASE] = LAYOUT_moonlander(
		D_ESC   , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , MO_FN   ,       MO_FN   , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_UP   ,
		KC_TAB  , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    , TG_PAD  ,       TG_PAD  , KC_Y    , KC_U    , KC_I    , KC_O    , KC_UNDS , KC_DOWN ,
		KC_BSPC , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    , KC_DEL  ,       KC_ESC  , KC_H    , KC_J    , KC_K    , KC_L    , KC_P    , MO_ACC  ,
		KC_LCTRL, KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    ,                           KC_N    , KC_M    , KC_COMMA, KC_DOT  , KC_QUOTE, KC_LCTRL,
		KC_LGUI , KC_LALT , MO_FN   , MO_NAV  , KC_LSFT ,           MO_MOD  ,       MO_MOD  ,           MO_SYM  , MO_NUM  , KC_LEFT , KC_RIGHT, TG_UTIL ,
		                                        KC_ENT  , KC_TAB  , KC_SPC  ,       KC_ENT  , SFT_TAB , KC_SPC
	),
	// Game:
	[LAYER_GAME] = LAYOUT_moonlander(
		KC_ESC  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_PAUSE,       KC_TRNS , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_TRNS ,
		KC_TAB  , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    , KC_DEL  ,       KC_TRNS , KC_TRNS , KC_TRNS , KC_UP   , KC_TRNS , KC_TRNS , KC_TRNS ,
		KC_LSFT , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    , KC_BSPC ,       KC_TRNS , KC_TRNS , KC_LEFT , KC_DOWN , KC_RIGHT, KC_TRNS , KC_TRNS ,
		KC_LCTRL, KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    ,                           KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		KC_GRAVE, KC_LALT , KC_TRNS , MO_GMA  , KC_SPC  ,           KC_ENT  ,       TO_GTYPE,           KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		                                        MO_GMB  , KC_CAPS , KC_TRNS ,       KC_TRNS , KC_TRNS , KC_TRNS
	),
	// Game typing:
	[LAYER_G_TYPE] = LAYOUT_moonlander(
		KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,       KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,       KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,       KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                           KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,           KC_TRNS ,       TO_GAME ,           KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		                                        KC_TRNS , KC_TRNS , KC_TRNS ,       KC_TRNS , KC_TRNS , KC_TRNS
	),
	// Modifiers:
	[LAYER_MODS] = LAYOUT_moonlander(
		KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,       KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , D_PRN   ,       D_PRN   , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		KC_TRNS , KC_LSFT , KC_LGUI , KC_LALT , KC_LCTRL, KC_TRNS , ALT_TAB ,       ALT_TAB , KC_TRNS , KC_RCTRL, KC_RALT , KC_RGUI , KC_RSFT , KC_TRNS ,
		KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                           KC_TRNS , KC_VOLU , KC_VOLD , KC_MUTE , KC_TRNS , KC_TRNS ,
		KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,           KC_TRNS ,       KC_TRNS ,           KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
		                                        KC_TRNS , KC_TRNS , KC_TRNS ,       KC_TRNS , KC_TRNS , KC_TRNS
	),
	// Symbols:
	[LAYER_SYM] = LAYOUT_moonlander(
		KC_TRNS , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_TRNS ,       KC_TRNS , KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  ,
		KC_TRNS , KC_CIRC , KC_LABK , KC_AMPR , KC_RABK , KC_TRNS , KC_TRNS ,       KC_TRNS , KC_TRNS , KC_SLASH, KC_BSLS , KC_ASTR , KC_PERC , KC_F12  ,
		KC_TRNS , KC_GRAVE, KC_COLN , KC_EQUAL, KC_MINUS, KC_PLUS , LANG_JP ,       LANG_EN , KC_LBRC , KC_LPRN , KC_LCBR , KC_QUES , KC_SCLN , KC_TRNS ,
		KC_TRNS , KC_DLR  , KC_PIPE , KC_DQUO , KC_EXLM , KC_TILD ,                           KC_RBRC , KC_RPRN , KC_RCBR , KC_AT   , KC_HASH , KC_TRNS ,
		KC_TRNS , KC_TRNS , KC_TRNS , KC_F22 ,  KC_F20  ,           KC_F21  ,       KC_TRNS ,           KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
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
		KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,       KC_TRNS , KC_CIRC , KC_ASTR , KC_SLASH, KC_PERC , KC_LPRN , KC_RPRN ,
		ALT_TAB , KC_WH_U , KC_HOME , KC_UP   , KC_END  , KC_PGUP , KC_TRNS ,       KC_TRNS , KC_EQUAL, KC_7    , KC_8     , KC_9   , KC_EQUAL, KC_INS  ,
		KC_BSPC , KC_WH_D , KC_LEFT , KC_DOWN , KC_RIGHT, KC_PGDN , KC_TRNS ,       KC_BSPC , KC_PLUS , KC_4    , KC_5     , KC_6   , KC_UP   , KC_DEL  ,
		KC_TRNS , KC_WH_L , KC_MS_L , KC_MS_U , KC_MS_R , KC_WH_R ,                           KC_MINUS, KC_1    , KC_2     , KC_3   , KC_LEFT , KC_RIGHT,
		KC_TRNS , KC_TRNS , KC_TRNS , KC_MS_D , KC_TRNS ,           KC_BTN3 ,       SFT_TAB ,           KC_0    , KC_DOT   , KC_COMM, KC_DOWN , KC_SCLN ,
		                                        KC_BTN1 , KC_BTN2 , KC_TRNS ,       KC_SPC  , KC_TAB  , KC_ENT
	),
};

extern bool g_suspend_state;
extern rgb_config_t rgb_matrix_config;

static uint32_t welcome_msg_timer = 0;
static bool welcome_msg_trigger = true;

void keyboard_post_init_user(void)
{
	rgb_matrix_enable();
	welcome_msg_timer = timer_read32();
	welcome_msg_trigger = false;
}

void matrix_scan_user(void)
{
	if (!welcome_msg_trigger) {
		if (timer_elapsed32(welcome_msg_timer) > 5000) {
			output("keyboard init: %dx%d (%d leds)", MATRIX_ROWS, MATRIX_COLS, DRIVER_LED_TOTAL);
			welcome_msg_trigger = true;
		}
	}
}

void set_layer_color(int layer)
{
	for (int i = 0; i < DRIVER_LED_TOTAL; i++)
	{
		HSV hsv = {
			.h = pgm_read_byte(&ledmap[layer][i][0]),
			.s = pgm_read_byte(&ledmap[layer][i][1]),
			.v = pgm_read_byte(&ledmap[layer][i][2]),
		};
		if (!hsv.h && !hsv.s && !hsv.v)
		{
			rgb_matrix_set_color(i, 0, 0, 0);
		}
		else
		{
			RGB rgb = hsv_to_rgb(hsv);
			float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
			rgb_matrix_set_color(i, f * rgb.r, f * rgb.g, f * rgb.b);
		}
	}
}

void rgb_matrix_indicators_user(void)
{
	if (g_suspend_state || keyboard_config.disable_layer_led)
	{
		return;
	}

	if (current_overlay.rgb != NULL) {
		current_overlay.rgb();
		return;
	}

	switch (biton32(layer_state))
	{
	case 0:
		set_layer_color(0);
		break;
	case 1:
		set_layer_color(1);
		break;
	case 2:
		set_layer_color(2);
		break;
	case 3:
		set_layer_color(3);
		break;
	case 4:
		set_layer_color(4);
		break;
	case 5:
		set_layer_color(5);
		break;
	case 6:
		set_layer_color(6);
		break;
	case 7:
		set_layer_color(7);
		break;
	case 8:
		set_layer_color(8);
		break;
	case 9:
		set_layer_color(9);
		break;
	case 10:
		set_layer_color(10);
		break;
	case 11:
		set_layer_color(11);
		break;
	case 12:
		set_layer_color(12);
		break;
	case 13:
		set_layer_color(13);
		break;
	case 14:
		set_layer_color(14);
		break;
	default:
		if (rgb_matrix_get_flags() == LED_FLAG_NONE)
			rgb_matrix_set_color_all(0, 0, 0);
		break;
	}
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
	static bool is_shift_pressed = false;

	if (keycode == KC_LSHIFT) {
		is_shift_pressed = record->event.pressed;
	}

	output("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n",
		keycode, record->event.key.col, record->event.key.row, record->event.pressed,
		record->event.time, record->tap.interrupted, record->tap.count);

	if (current_overlay.process != NULL) {
		if (!record->event.pressed && current_overlay_skip_not_pressed) {
			current_overlay_skip_not_pressed = false;
			return false;
		} else {
			current_overlay_skip_not_pressed = false;
		}
		return current_overlay.process(keycode, record);
	}

	if (record->event.key.col == 6 && record->event.key.row == 0 && is_shift_pressed) {
		unregister_code(KC_LSHIFT);
		if (!record->event.pressed) {
			open_menu();
		}
		return false;
	}

	switch (keycode)
	{
	case RGB_SLD:
		if (record->event.pressed)
		{
			rgblight_mode(1);
		}
		return false;
	}
	return true;
}

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

static tap dance_state[16];

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
	dance_state[0].step = dance_step(state);
	switch (dance_state[0].step)
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
	switch (dance_state[0].step)
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
	dance_state[0].step = 0;
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
	dance_state[3].step = dance_step(state);
	switch (dance_state[3].step)
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
	switch (dance_state[3].step)
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
	dance_state[3].step = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
	[DANCE_0] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_esc, dance_esc_finished, dance_esc_reset),
	[DANCE_1] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_prn, dance_prn_finished, dance_prn_reset),
};
