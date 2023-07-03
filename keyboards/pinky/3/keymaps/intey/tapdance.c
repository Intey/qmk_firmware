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
        if ( // state->interrupted ||
            !state->pressed) {
            return TD_SINGLE_TAP;
        }
        // key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
        else {
            return TD_SINGLE_HOLD;
        }
    } else if (state->count == 2) {
        /*
         * TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
         * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
         * keystrokes of the key, and not the 'double tap' action/macro.
         */

        // if (state->interrupted) {
        //     return TD_DOUBLE_SINGLE_TAP;
        // } else
        if (state->pressed) {
            return TD_DOUBLE_HOLD;
        } else {
            return TD_DOUBLE_TAP;
        }
    } else if (state->count == 3) {
        if ( // state->interrupted ||
            !state->pressed) {
            return TD_TRIPLE_TAP;
        }
        return TD_TRIPLE_HOLD;
    } else if (state->count == 4) {
        uprintf("quad detect");
        if ( // state->interrupted ||
            !state->pressed) {
            return TD_QUAD_TAP;
        }
        return TD_QUAD_HOLD;
    } else {
        return TD_UNKNOWN;
    }
    return TD_UNKNOWN;
}

// Functions that control what our tap dance key does
void awesome_finished(qk_tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_HOLD:
            layer_on(NUMBERS);
            register_code16(KC_LGUI);
            break;
        case TD_DOUBLE_HOLD:
            register_code16(KC_LGUI);
            break;
        default:
            break;
    }
}

void awesome_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(NUMBERS);
    } else if (ql_tap_state.state == TD_DOUBLE_HOLD) {
        unregister_mods(MOD_LSFT);
    } else if (ql_tap_state.state == TD_TRIPLE_HOLD) {
        layer_off(NUMBERS);
        unregister_mods(MOD_LSFT);
    }
    unregister_code16(KC_LGUI);
    ql_tap_state.state = TD_NONE;
}

void grave_home_dance(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        int mod_state = get_mods();
        // if shift is held - unshift (send grave) and restore
        if (mod_state & MOD_MASK_SHIFT) {
            // TODO: still sends an tild
            uprintf("send grv\n");
            unregister_mods(MOD_LSFT);
            tap_code(KC_GRV);
            register_mods(MOD_LSFT);
        } else {
            uprintf("send tild\n");
            register_mods(MOD_LSFT);
            tap_code(KC_GRV);
            unregister_mods(MOD_LSFT);
        }
    } else if (state->count == 2) {
        // in dvorak we need to send '[' instead '/' because they swapped
        SEND_STRING("~[");
    }
    reset_tap_dance(state);
}

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [AWE]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, awesome_finished, awesome_reset), //
    [GRV_HOME] = ACTION_TAP_DANCE_FN(grave_home_dance)                      //
};
