#include QMK_KEYBOARD_H
#include "defs.h"
#include "keymap_dvorak.h"

#define NAV MO(NAVIGATION)
#define SF_DEL LSFT_T(KC_DEL)
#define ALT_TAB LALT_T(KC_TAB)
#define LTL_SPS LCTL_T(KC_SPC)
#define RTL_SPS RCTL_T(KC_SPC)
#define NUMBERS MO(NUMBERS)
#define TD_AWE TD(AWE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x7_4(
          KC_ESC,  DV_QUOT,  DV_COMM,  DV_DOT,    DV_P,     DV_Y,       DV_LPRN,  /**/ DV_RPRN,     DV_F,    DV_G,     DV_C,  DV_R,  DV_L,   DV_EQL,
         DV_SLSH,     DV_A,     DV_O,    DV_E,    DV_U,     DV_I,       DV_LBRC,  /**/ DV_RBRC,     DV_D,    DV_H,     DV_T,  DV_N,  DV_S,  DV_MINS,
         DV_BSLS,  DV_SCLN,     DV_Q,    DV_J,    DV_K,     DV_X,  TD(GRV_HOME),  /**/  KC_ENT,     DV_B,    DV_M,     DV_W,  DV_V,  DV_Z,  KC_BSPC,
                                          NAV,  SF_DEL,  ALT_TAB,       LTL_SPS,  /**/ RTL_SPS,  NUMBERS,  TD_AWE,  KC_LSFT
                                        ),

    [1] = LAYOUT_split_3x7_4(
          KC_GRV,  KC_WH_L,  KC_WH_D,  KC_WH_U,  KC_WH_R,  KC_BTN2,  _______,  /*  */ _______,  _______,  KC_HOME,   KC_PGDN,  KC_PGUP,   KC_END,  KC_BSLS,
         _______,  KC_MS_L,  KC_MS_D,  KC_MS_U,  KC_MS_R,  KC_BTN1,  _______,  /*  */ _______,  C(DV_C),  KC_LEFT,   KC_DOWN,    KC_UP,  KC_RGHT,  _______,
         _______,  AWSM_LW,   AWSM_L,   AWSM_R,  AWSM_RW,  KC_BTN3,  KC_CAPS,  /*  */ _______,  C(DV_X),  KC_BTN1,   KC_BTN2,  C(DV_V),  KC_BTN3,  _______,
                                       _______,  _______,  _______,    TG(3),  /*  */ _______,  _______,  _______,  _______),

    [2] = LAYOUT_split_3x7_4(
         DV_LBRC,  KC_F1,   KC_F2,    KC_F3,    KC_F4,  _______,    _______,     /*  */ _______,  S(KC_MINS),     KC_1,      KC_2,     KC_3,     KC_4,     KC_5,
         _______,  KC_F5,   KC_F6,    KC_F7,    KC_F8,  _______,     KC_GRV,     /*  */ DV_SLSH,      KC_EQL,     KC_6,      KC_7,     KC_8,     KC_9,     KC_0,
         DV_RBRC,  KC_F9,  KC_F10,   KC_F11,   KC_F12,  _______,  S(KC_GRV),  /*  */ S(DV_SLSH),     _______,   DV_DOT,   DV_MINS,  DV_COMM,  _______,  _______,
                                    _______,  _______,  _______,    _______,     /*  */ _______,     _______,  _______,  _______),

    [3] = LAYOUT_split_3x7_4(                                                      /* Left-hander QWERTY for gaming */
         _______,  _______,  _______,  _______,  _______,  _______,  _______,   /*  */ KC_TAB,    DV_I,   DV_Q,    DV_W,  DV_E,  DV_R,  DV_T,
         _______,  _______,  _______,  _______,  _______,  _______,  _______,  /*  */ KC_LALT,    DV_H,   DV_A,    DV_S,  DV_D,  DV_F,  DV_G,
         _______,  _______,  _______,  _______,  _______,  _______,  _______,  /*  */ KC_LSFT,    DV_M,   DV_Z,    DV_X,  DV_C,  DV_V,  DV_B,
                                       XXXXXXX,  _______,  _______,    TG(3),  /*  */ KC_LCTL,  KC_SPC,  MO(4),  KC_ESC
                                    ),
   [4] = LAYOUT_split_3x7_4(
         _______,  _______,  _______,  _______,  _______,  _______,  _______,  /*  */ _______,  _______,     KC_1,      KC_2,  KC_3,   DV_EQL,   KC_DEL,
         _______,  _______,  _______,  _______,  _______,  _______,  _______,  /*  */ _______,  _______,     KC_4,      KC_5,  KC_6,     KC_0,  _______,
         _______,  _______,  _______,  _______,  _______,  _______,  _______,  /*  */ _______,  _______,     KC_7,      KC_8,  KC_9,  DV_MINS,  _______,
                                       _______,  _______,  _______,  _______,  /*  */ _______,  _______,  _______,  _______)
   // [5] = LAYOUT_split_3x7_4(
   //   _______,  _______,  _______,  _______,  _______,  _______,  _______,  /*  */ _______,  _______,  _______,  _______,  _______,  _______,  _______,
   //   _______,  _______,  _______,  _______,  _______,  _______,  _______,  /*  */ _______,  _______,  _______,  _______,  _______,  _______,  _______,
   //   _______,  _______,  _______,  _______,  _______,  _______,  _______,  /*  */ _______,  _______,  _______,  _______,  _______,  _______,  _______,
   //                                 _______,  _______,  _______,  _______,  /*  */ _______,  _______,  _______,  _______)
};

uint8_t mod_state;

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

  //   mod_state = get_mods();
  // bool should_unshift = keycode & keys_to_unshift;

  // switch (keycode) {
  //   case HMMACRO:
  //   if (record->event.pressed) {
  //       SEND_STRING("~/");
  //   }
  // }
      /*
      // initialize a boolean variable that keeps track
        // of the delete key status: registered or not?
        static bool delkey_registered;

            // Detect the activation of either shift keys
            if (mod_state & MOD_MASK_SHIFT) {
                // First temporarily canceling both shifts so that
                // shift isn't applied to the KC_DEL keycode
                del_mods(MOD_MASK_SHIFT);
                register_code(KC_DEL);
                // Update the boolean variable to reflect the status of KC_DEL
                delkey_registered = true;
                // Reapplying modifier state so that the held shift key(s)
                // still work even after having tapped the Backspace/Delete key.
                set_mods(mod_state);
                return false;
            }
        } else { // on release of KC_BSPC
            // In case KC_DEL is still being sent even after the release of KC_BSPC
            if (delkey_registered) {
                unregister_code(KC_DEL);
                delkey_registered = false;
                return false;
            }
        }
        // Let QMK process the KC_BSPC keycode as usual outside of shift
        return true;
    }

    }
  // unshift symbols
*/
  return true;
}
