#pragma once
#include <stdbool.h>
#include "quantum.h"

/* TODO:
   By default, instead nums we meet symbols on num keys, and with shift - nums, like in dvorak for programmer.
 */
#define AWSM_L LGUI(DV_K)
#define AWSM_R LGUI(DV_J)
#define AWSM_RW LGUI(KC_RGHT)
#define AWSM_LW LGUI(KC_LEFT)

typedef enum {
    NUMBERS,
    NAVIGATION
} LAYERS;

// Define a type for as many tap dance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_SINGLE_TAP,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

struct td_tap_t {
    bool is_press_action;
    td_state_t state;
};

enum {
  AWE, // Our custom tap dance key; add any other tap dance keys to this enum 
  GRV_HOME,
};
