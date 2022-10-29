/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)
Copyright 2022 goropikari

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"

enum layer_names {
    _DVORAK = 0,
    _LOWER,
    _RAISE,
    _ADJUST,
    _MOUSE,
    _TRACKBALL_SETTING,
};

enum my_keycodes {
  SCRL_MODE = KEYBALL_SAFE_RANGE,
  SPC_EXIT,
  MV_LTAB, // move browser left tab
  MV_RTAB, // move browser right tab
  GO_L_DVORAK, // BASE layer の永続化
  GO_L_MOUSE, // MOUSE layer の永続化
};

// SandS
#define KC_MT_SS MT(MOD_LSFT, KC_SPC)

#define KC_CTLTB CTL_T(KC_TAB)
#define KC_CTL_SCLN CTL_T(KC_SCLN)
#define CTRL_SHFT MT(MOD_LCTL | MOD_LSFT, KC_ESC)
#define XXXXX KC_NO
#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ADJUST MO(_ADJUST)
#define MOUSE  MO(_MOUSE)
#define TRACKB TG(_TRACKBALL_SETTING)

#define LCLICK KC_BTN1
#define RCLICK KC_BTN2
#define CCLICK KC_BTN3
// web page back
#define BACK   KC_BTN4
// web page forward
#define FORWARD KC_BTN5

bool on_mouse_layer = false;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default
  [_DVORAK] = LAYOUT_universal(
    KC_QUOT     , KC_COMM  , KC_DOT   , KC_P            , KC_Y                 ,                                 KC_F     , KC_G     , KC_C     , KC_R     , KC_L     ,
    KC_A        , KC_O     , KC_E     , KC_U            , KC_I                 ,                                 KC_D     , KC_H     , KC_T     , KC_N     , KC_S     ,
    KC_SCLN     , KC_Q     , KC_J     , KC_K            , KC_X                 ,                                 KC_B     , KC_M     , KC_W     , KC_V     , KC_Z     ,
    MOUSE       , XXXXX    , XXXXX    , RGUI_T(KC_ESC)  , LT(_LOWER, KC_MINS)  , KC_CTLTB , LT(_RAISE, KC_ENT) , KC_MT_SS ,XXXXX    , XXXXX    , XXXXX     , MOUSE
  ),

  [_LOWER] = LAYOUT_universal(
    CTRL_SHFT   , KC_S     , KC_P     , XXXXX    , KC_TAB   ,                      KC_CIRC   , KC_AMPR  , KC_UP    , KC_LPRN  , KC_RPRN  ,
    KC_CTLTB    , KC_A     , KC_Z     , KC_C     , KC_X     ,                      KC_HOME   , KC_LEFT  , KC_DOWN  , KC_RIGHT , KC_BSPC  ,
    XXXXX       , XXXXX    , XXXXX    , XXXXX    , XXXXX    ,                      KC_END    , KC_ENT   ,  XXXXX   , XXXXX    , KC_DEL   ,
    XXXXX       , XXXXX    , XXXXX    , KC_RGUI  , LOWER    , KC_RALT  ,  ADJUST,  KC_MT_SS  , XXXXX    ,  XXXXX   , XXXXX    , XXXXX
  ),

  [_RAISE] = LAYOUT_universal(
    KC_1     , KC_2     , KC_3     , KC_4     , KC_5     ,                      XXXXX    ,  XXXXX    , KC_TAB   , KC_SLSH  , S(KC_SLSH)  ,
    KC_6     , KC_7     , KC_8     , KC_9     , KC_0     ,                      KC_PIPE  ,  KC_BSLS  , KC_GRV   , KC_EQL   , KC_EQL      ,
    XXXXX    , XXXXX    , XXXXX    , XXXXX    , XXXXX    ,                      KC_ENT   ,  KC_PLUS  , KC_TILD  , XXXXX    , XXXXX       ,
    XXXXX    , XXXXX    , XXXXX    , KC_RGUI  , ADJUST   , KC_RALT,  XXXXX   ,  XXXXX    ,  XXXXX    , XXXXX    , XXXXX    , XXXXX
  ),

  [_ADJUST] = LAYOUT_universal(
    KC_EXLM , KC_AT     , KC_HASH   , KC_DLR    , KC_PERC   ,                      KC_CIRC    , KC_AMPR   , KC_ASTR   , KC_LBRC   , KC_RBRC   ,
    XXXXX   , XXXXX     , XXXXX     , XXXXX     , XXXXX     ,                      KC_PIPE    , KC_BSLS   , XXXXX     , S(KC_LBRC), S(KC_RBRC),
    KC_F1   , KC_F2     , KC_F3     , KC_F4     , KC_F5     ,                      KC_F6      , KC_F7     , KC_F8     , KC_F9     , KC_F10    ,
    XXXXX   , XXXXX     , XXXXX     , XXXXX     , XXXXX     , XXXXX   ,  XXXXX   , XXXXX      , XXXXX     , XXXXX     , XXXXX     , XXXXX
  ),

  [_MOUSE] = LAYOUT_universal(
    TRACKB      , MV_LTAB   , XXXXX     , MV_RTAB   , XXXXX       ,                        XXXXX       , MV_LTAB   , XXXXX     , MV_RTAB , XXXXX     ,
    GO_L_MOUSE  , LCLICK    , CCLICK    , RCLICK    , GO_L_MOUSE  ,                        GO_L_MOUSE  , LCLICK    , CCLICK    , RCLICK  , SCRL_MODE ,
    GO_L_DVORAK , BACK      , SCRL_MODE , FORWARD   , GO_L_DVORAK ,                        GO_L_DVORAK , BACK      , SCRL_MODE , FORWARD , XXXXX     ,
    XXXXX       , XXXXX     , XXXXX     , KC_ESC    , GO_L_DVORAK , KC_CTLTB ,   KC_ENT  , KC_SPC      , XXXXX     , XXXXX     , XXXXX   , XXXXX
  ),

  [_TRACKBALL_SETTING] = LAYOUT_universal(
    // KBC_RST   トラックボールの設定をリセットする
    // KBC_SAVE  トラックボールの設定を保存する。保存しないと USB をつなぎ直したときに設定がリセットされる。
    // KBC_I100  トラックボールの感度を 100 上げる
    // KBC_I1K   トラックボールの感度を 1000 上げる
    // KBC_D100  トラックボールの感度を 100 下げる
    // KBC_D1K   トラックボールの感度を 1000 下げる
    // https://github.com/Yowkees/keyball/blob/be5ef1009116af22533c0b8b72ae2fb7db9b8610/qmk_firmware/keyboards/keyball/keyball39/readme.md
    TG(_TRACKBALL_SETTING), XXXXX   , XXXXX    , XXXXX , XXXXX ,                   XXXXX , XXXXX , XXXXX , XXXXX , XXXXX ,
    KBC_RST           , KBC_SAVE, XXXXX    , XXXXX , XXXXX ,                   XXXXX , XXXXX , XXXXX , XXXXX , XXXXX ,
    CPI_I100          , CPI_I1K , SCRL_DVI , XXXXX , XXXXX ,                   XXXXX , XXXXX , XXXXX , XXXXX , XXXXX ,
    CPI_D100          , CPI_D1K , SCRL_DVD , XXXXX , XXXXX , XXXXX ,   XXXXX , XXXXX , XXXXX , XXXXX , XXXXX , XXXXX
  ),
};
// clang-format on

void trackball_on(void) {
  if (is_keyboard_left()) {
    keyball.this_have_ball = false;
    keyball.that_have_ball = true;
  } else {
    keyball.this_have_ball = true;
    keyball.that_have_ball = false;
  }
}

void trackball_off(void) {
  keyball.this_have_ball = false;
  keyball.that_have_ball = false;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // mouse layer でない場合はスクロールモードを off にする
    if (get_highest_layer(state) != _MOUSE) {
      keyball_set_scroll_mode(0);
    }

    // mouse layer のときだけ trackball を有効にする
    if (get_highest_layer(state) == _MOUSE || on_mouse_layer) {
      trackball_on();
    } else {
      trackball_off();
    }

    // 左右のどちらに USB が接続されているかでレイヤーを分けたい場合に使う
    // if (on_mouse_layer) return state;
    // if (is_keyboard_master() && is_keyboard_left()) {
    //   on_mouse_layer = false;
    //   set_single_persistent_default_layer(_DVORAK);
    //   keyball_set_scroll_mode(0);
    // } else {
    //   on_mouse_layer = false;
    //   set_single_persistent_default_layer(_QWERTY);
    //   keyball_set_scroll_mode(0);
    // }
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SCRL_MODE:
      if (record->event.pressed) {
        bool currState = keyball_get_scroll_mode();
        keyball_set_scroll_mode(!currState);
      }
      return false; // Skip all further processing of this key
    case SPC_EXIT: // space を押したら mouse layer から出る
      if (record->event.pressed) {
        keyball_set_scroll_mode(false);
        layer_off(_MOUSE);
        register_code(KC_SPC);
        unregister_code(KC_SPC);
        layer_on(_DVORAK);
        return false;
      }
    case MV_RTAB:
      if (record->event.pressed) {
        register_code(KC_LCTL);
        register_code(KC_TAB);
        unregister_code(KC_TAB);
        unregister_code(KC_LCTL);
      }
      return false;
    case MV_LTAB:
      if (record->event.pressed) {
        register_code(KC_LCTL);
        register_code(KC_LSFT);
        register_code(KC_TAB);
        unregister_code(KC_TAB);
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
      }
      return false;
    case GO_L_DVORAK:
      if (record->event.pressed) {
        on_mouse_layer = false;
        set_single_persistent_default_layer(_DVORAK);
        keyball_set_scroll_mode(0);
        trackball_off();
      }
      return false;
    case GO_L_MOUSE:
      if (record->event.pressed) {
        on_mouse_layer = true;
        // set_single_persistent_default_layer は EEPROM に設定を書き込むので MOUSE layer のまま USB を外すと、次につないだときに MOUSE layer から始まるので注意
        set_single_persistent_default_layer(_MOUSE);
        trackball_on();
      }
      return false;
    default:
      return true; // Process all other keycodes normally
  }
}

#ifdef OLED_ENABLE

#include "lib/oledkit/oledkit.h"

void keyball_oled_render_layerinfo(void) {
#ifdef OLED_ENABLE
    oled_write_P(PSTR("L: "), false);
    switch (get_highest_layer(layer_state)) {
    case 0:
      if (on_mouse_layer) oled_write_P(PSTR("Mouse"), false);
      else oled_write_P(PSTR("Default"), false);
      break;
    case _LOWER:
      oled_write_P(PSTR("Lower"), false);
      break;
    case _RAISE:
      oled_write_P(PSTR("Raise"), false);
      break;
    case _ADJUST:
      oled_write_P(PSTR("Adjust"), false);
      break;
    case _MOUSE:
      oled_write_P(PSTR("Mouse"), false);
      break;
    case _TRACKBALL_SETTING:
      oled_write_P(PSTR("Setting"), false);
      break;
    default:
      oled_write_P(PSTR("Unknown"), false);
    }
#endif
}

void mouse_layer_logo(void) {
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,192,192,192,128,  0,  0,  0,  0,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255, 30,112,192,  0,  0,  0,  0,  0,  0,  0,  0,192,112, 28,  7,255,  0,  0,  0,  0,  0,  0,128,128,192, 64, 64, 64, 64,192,128,  0,  0,  0,  0,  0,  0,192,192,  0,  0,  0,  0,  0,  0,  0,192,192,  0,  0,  0,  0,  0,128,192, 64, 64, 64, 64, 64,192,192,  0,  0,  0,  0,  0,128,192,192, 64, 64, 64,192,192,128,  0,  0,  0,  0,  0,  0,  0,207,255,249,248,249,125,127,255,254,255,231,195,199,255,255,126,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,  0,  0,  1,  7, 60,240,192,192,112, 28,  7,  1,  0,  0,  0,255,  0,  0,  0,  0, 48,254,  3,  1,  0,  0,  0,  0,  0,  0,  1,207,254,  0,  0,  0,  0,255,255,  0,  0,  0,  0,  0,  0,  0,255,255,  0,  0,  0,  0,  2, 15, 24, 24, 16, 48, 48, 32, 96,192,  0,  0,  0, 48,254, 19, 16, 16, 16, 16, 16, 16, 17, 23, 30,  0,  0,  0,  0,  0, 31, 31, 31, 31,239,127,126,126, 63,255,255,255,255,255,255,255,254,252,240,192,192,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 15, 15,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0, 15,  0,  0,  0,  0,  0,  1,  7, 14, 12,  8,  8,  8,  8, 12,  6,  3,  1,  0,  0,  0,  0,  1,  7, 14, 12,  8,  8,  8,  8, 12,  7, 15,  0,  0,  0,  0,  4, 12, 12,  8,  8,  8,  8,  8, 12,  7,  1,  0,  0,  0,  1,  7,  6, 12,  8,  8,  8,  8,  8, 12,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 22, 23, 55, 33, 44,126,110,111,103,103, 51, 51, 49, 24, 31, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

void keyball_info(void) {
  keyball_oled_render_layerinfo();
  keyball_oled_render_keyinfo();
  keyball_oled_render_ballinfo();
}

void render_user_oled(void) {
  int layer = get_highest_layer(layer_state);
  if (layer == _TRACKBALL_SETTING) {
    keyball_info();
  } else if (on_mouse_layer || layer == _MOUSE) {
    mouse_layer_logo();
  } else {
    keyball_info();
  }
}

// OLED の表示
bool oled_task_user(void) {
  oled_clear();
  if (is_keyboard_master()) {
    render_user_oled();
  } else {
    oledkit_render_logo_user(); // keyball logo
  }
  return true;
}
#endif
