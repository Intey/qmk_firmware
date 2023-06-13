#include <stdio.h>
#include "defs.h"
#include "quantum.h"

// Initialize tap structure associated with example tap dance key
static struct td_tap_t ql_tap_state = {.is_press_action = true, .state = TD_NONE};

// awesome tweaks:
// single hold - just LGUI key
// double hold - LGUI + NUMBER
// triple hold - LGUI + SHIFT
// quad hold - LGUI + SHIFT + NUMBER

// numbers tweak:
// hold - numbers layer
// double hold - NUMBERS + SHIFT

// Determine the current tap dance state
//// BEGIN: Advanced Tap Dances
int cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) {
            uprintf("single tap\n");
            return TD_SINGLE_TAP;
        }
        // key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
        else {
            uprintf("single hold\n");
            return TD_SINGLE_HOLD;
        }
    } else if (state->count == 2) {
        /*
         * TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
         * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
         * keystrokes of the key, and not the 'double tap' action/macro.
         */
        if (state->interrupted) {
            uprintf("double tap\n");
            return TD_DOUBLE_SINGLE_TAP;
        } else if (state->pressed) {
            uprintf("double hold\n");

            return TD_DOUBLE_HOLD;
        } else {
            uprintf("double tap\n");
            return TD_DOUBLE_TAP;
        }
    }
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) {
            uprintf("triple tap\n");
            return TD_TRIPLE_TAP;
        }
        uprintf("triple hold\n");
        return TD_TRIPLE_HOLD;
    } else {
        return TD_UNKNOWN;
    }
    return TD_UNKNOWN;
}

// Functions that control what our tap dance key does
void ql_finished(qk_tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_HOLD:
            layer_on(NUMBERS);
            register_code16(KC_LGUI);
            break;
        case TD_DOUBLE_HOLD:
            if (!layer_state_is(NUMBERS)) {
                layer_on(NUMBERS);
            }
            register_mods(MOD_LSFT);
            register_code16(KC_LGUI);
            break;
        case TD_TRIPLE_HOLD:
            register_code16(KC_LGUI);
        default:
            break;
    }
}

void ql_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(NUMBERS);
    } else if (ql_tap_state.state == TD_DOUBLE_HOLD) {
        layer_off(NUMBERS);
        unregister_mods(MOD_LSFT);
    }
    unregister_code16(KC_LGUI);
    ql_tap_state.state = TD_NONE;
}

// Set a long-ish tapping term for tap-dance keys
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case GRV_HOME:
            return TAPPING_TERM;
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            return 275;
        default:
            return TAPPING_TERM;
    }
}

void grave_home_dance(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        int mod_state = get_mods();
        // if shift is held - unshift (send grave) and restore
        if (mod_state & MOD_MASK_SHIFT) {
            del_mods(MOD_MASK_SHIFT);
            tap_code(KC_GRV);
            set_mods(mod_state);
            // send tild
        } else {
            add_mods(MOD_BIT(MOD_LSFT));
            tap_code(KC_GRV);
            set_mods(mod_state);
        }
    } else if (state->count == 2) {
        // in dvorak we need to send '[' instead '/' because they swapped
        SEND_STRING("~[");
    }
    reset_tap_dance(state);
}

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [AWE]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ql_finished, ql_reset), //
    [GRV_HOME] = ACTION_TAP_DANCE_FN(grave_home_dance)                      //
};
