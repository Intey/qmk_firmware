#include QMK_KEYBOARD_H

/* TODO: 
   - [ ] make combos and place Awesome hotkeys like LGUI(KC_R)

 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_split_3x7_4(
      KC_GRV,  KC_SCLN, KC_COMM, KC_DOT,  KC_P,    KC_Y,               KC_LPRN, /*  */ KC_RPRN,        KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_EQL, 
      KC_LCTL, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,               KC_LBRC, /*  */ KC_RBRC,        KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS, 
      KC_SLSH, KC_QUOT, KC_Q,    KC_J,    KC_K,    KC_X,               KC_ESC,  /*  */ KC_ENT,         KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_BSPC, 
                                 MO(1),   MO(2),   LSFT_T(KC_TILDE), KC_SPC,  /*  */ LCTL_T(KC_TAB), KC_LGUI, KC_LALT, KC_DEL), 
    [1] = LAYOUT_split_3x7_4(
      KC_GRV,  _______, _______, _______, _______, _______,            KC_CAPS, /*  */ _______,        _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_BSLS, 
      _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______,            _______, /*  */ _______,        C(KC_C), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, 
      _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, _______,            _______, /*  */ _______,        C(KC_X), KC_BTN1, KC_BTN2, KC_BTN3, C(KC_V), _______, 
                                 _______, _______, _______,            _______, /*  */ _______,        _______, _______, _______), 
    [2] = LAYOUT_split_3x7_4(
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,              KC_F6,   /*  */ KC_F7,          KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS, 
      KC_GRV,  KC_7,    KC_5,    KC_3,    KC_1,    KC_9,               _______, /*  */ _______,        KC_0,    KC_2,    KC_4,    KC_6,    KC_8,    KC_BSLS, 
      _______, _______, _______, _______, _______, _______,            _______, /*  */ _______,        _______, _______, _______, _______, _______, _______, 
                                 _______, _______, _______,            _______, /*  */ _______,        _______, _______, _______)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
  uprintf("0x%04X,%u,%u,%u,%b,0x%02X,0x%02X,%u\n",
      keycode,
      record->event.key.row,
      record->event.key.col,
      get_highest_layer(layer_state),
      record->event.pressed,
      get_mods(),
      get_oneshot_mods(),
      record->tap.count
      );
#endif
  return true;
}
