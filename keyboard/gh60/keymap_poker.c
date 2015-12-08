#include "action_layer.h"
#include "keymap_common.h"
#include "led.h"
#include "keyboard.h"
#include "host.h"
#include "command.h"
#include "action.h"
#include "action_tapping.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    
    /* 0: workman */
    KEYMAP(GRV, FN5,FN26,FN27,FN28,FN21,  F5,HOME,FN29,FN30,FN31, FN8,FN24,FN25, \
           TAB,   Q,   D,   R,   W,   B, ESC, EQL,   J,   F,   U,   P,SCLN,BSLS, \
           LCTL,  A,   S,   H,   T,   G, DEL,MINS,   Y,   N,   E,   O,   I,QUOT, \
           FN6,   Z,   X,   M,   C,   V, FN2,RGUI,   K,   L,COMM, DOT,SLSH, FN7, \
           CAPS,FN9,FN10,LALT, FN0,SPC, ENT, ENT,BSPC,RALT,LBRC,RBRC,FN23,RCTL),

    /* 1: qwerty */
    KEYMAP(TRNS,  1,   2,   3,   4,   5,TRNS,TRNS,   6,   7,   8,   9,   0,TRNS, \
           TRNS,  Q,   W,   E,   R,   T,TRNS,TRNS,   Y,   U,   I,   O,   P,TRNS, \
           TRNS,  A,   S,   D,   F,   G,TRNS,TRNS,   H,   J,   K,   L,SCLN,TRNS, \
           LSFT,  Z,   X,   C,   V,   B,TRNS,TRNS,   N,   M,COMM, DOT,SLSH,RSFT, \
           TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS),

    /* 2: navigation */
    KEYMAP( FN4,  F1,  F2,  F3,  F4,  F5, FN3,TRNS, F6,  F7,  F8,   F9,F10, FN1, \
           TRNS,CAPS,FN17,FN18,  NO,  NO,TRNS,TRNS,FN14,FN15,FN13,FN16, NO,TRNS, \
           TRNS,  NO,FN22,  NO,FN19,  NO,TRNS,TRNS,LEFT,DOWN,  UP,RGHT, NO,TRNS, \
           TRNS,  NO,  NO,FN21,FN20,  NO,TRNS,TRNS,HOME,PGDN,PGUP, END, NO,TRNS, \
           TRNS,MUTE,F12,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,PAUS),

    /* 3: numpad */
    KEYMAP( FN4,  F1,  F2,  F3,  F4,  F5, FN3,TRNS, F6,  F7,  F8,  F9, F10, FN1, \
           TRNS,  NO,  NO,  NO,  NO,  NO,TRNS,TRNS, NO,   7,   8,   9,  NO,TRNS, \
           TRNS,  NO,  NO,  NO,  NO,  NO,TRNS,TRNS, NO,   4,   5,   6,  NO,TRNS, \
           TRNS,  NO,  NO,  NO,  NO,  NO,TRNS,TRNS, NO,   1,   2,   3,  NO,TRNS, \
           TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,  0,   0,PDOT,TRNS,PAUS),

};

enum function_id {
    LEFT_SHIFT,
    RIGHT_SHIFT,
    SHIFTED_1,
    SHIFTED_2,
    SHIFTED_3,
    SHIFTED_4,
    SHIFTED_5,
    SHIFTED_6,
    SHIFTED_7,
    SHIFTED_8,
    SHIFTED_9,
    SHIFTED_0,
};

const uint16_t PROGMEM fn_actions[] = {
    // layer functions
    [0] = ACTION_LAYER_MOMENTARY(2), // navigation
    [1] = ACTION_LAYER_TOGGLE(1), // qwerty
    [2] = ACTION_LAYER_MOMENTARY(3), // numpad
    // hotkeys
    [3] = ACTION_MODS_KEY(MOD_LALT,KC_F4), // alt f4
    [4] = ACTION_MODS_KEY(MOD_LCTL | MOD_LALT, KC_DEL), // ctrl alt del 
    [9] = ACTION_MODS_KEY(MOD_LCTL, KC_C), // copy
    [10] = ACTION_MODS_KEY(MOD_LCTL, KC_V), // paste
    // windows key shortcuts
    [11] = ACTION_MODS_KEY(MOD_RGUI, KC_E), // open computer
    [12] = ACTION_MODS_KEY(MOD_RGUI, KC_R), // run
    [13] = ACTION_MODS_KEY(MOD_RGUI, KC_UP), // gui up
    [14] = ACTION_MODS_KEY(MOD_RGUI, KC_LEFT), // gui left
    [15] = ACTION_MODS_KEY(MOD_RGUI, KC_DOWN), // gui down
    [16] = ACTION_MODS_KEY(MOD_RGUI, KC_RIGHT), // gui right 
    [17] = ACTION_MODS_KEY(MOD_RGUI, KC_D), // desktop
    [18] = ACTION_MODS_KEY(MOD_RGUI, KC_R), // run
    [19] = ACTION_MODS_KEY(MOD_RGUI, KC_T), // cycle tabs
    [20] = ACTION_MODS_KEY(MOD_RGUI, KC_E), // my computer
    [22] = ACTION_MODS_KEY(MOD_RGUI, KC_S), // search
    [23] = ACTION_MODS_KEY(MOD_LCTL | MOD_LSFT, KC_ESC), // task manager
    [25] = ACTION_LAYER_SET_CLEAR(0), // clear all layers
    // shift actions
    [6] = ACTION_FUNCTION(LEFT_SHIFT),
    [7] = ACTION_FUNCTION(RIGHT_SHIFT),
    // number actions
    [5] = ACTION_FUNCTION(SHIFTED_1),
    [26] = ACTION_FUNCTION(SHIFTED_2),
    [27] = ACTION_FUNCTION(SHIFTED_3),
    [28] = ACTION_FUNCTION(SHIFTED_4),
    [21] = ACTION_FUNCTION(SHIFTED_5),
    [29] = ACTION_FUNCTION(SHIFTED_6),
    [30] = ACTION_FUNCTION(SHIFTED_7),
    [31] = ACTION_FUNCTION(SHIFTED_8),
    [8] = ACTION_FUNCTION(SHIFTED_9),
    [24] = ACTION_FUNCTION(SHIFTED_0),
};

static uint8_t shift_key_state;

// pass in key state and keycode and it will reverse shift behavior
void reverse_shift(uint8_t pressed, uint8_t key) {
    if (pressed) {
	flip_mods(MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT));
	add_key(key);
	send_keyboard_report();
    } else {
	// check if a shift KEY is active
	if (shift_key_state&MOD_BIT(KC_LSHIFT)) {
	    // if so, then add the modifier back
	    add_mods(MOD_BIT(KC_LSHIFT));
	} else {
	    // otherwise remove
	    del_mods(MOD_BIT(KC_LSHIFT));
	}
        if (shift_key_state&MOD_BIT(KC_RSHIFT)) {
	    add_mods(MOD_BIT(KC_RSHIFT));
	} else {
	    del_mods(MOD_BIT(KC_RSHIFT));
	}
	del_key(key);
	send_keyboard_report();
    }
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
	// special shift functions to track key states
    	case LEFT_SHIFT:						
	    if (record->event.pressed) {
		shift_key_state |= MOD_BIT(KC_LSHIFT);
		register_code(KC_LSHIFT);
		send_keyboard_report();
	    } else {
		shift_key_state &= ~MOD_BIT(KC_LSHIFT);
		unregister_code(KC_LSHIFT);
		send_keyboard_report();
	    }
	    break;
	case RIGHT_SHIFT:
	    if (record->event.pressed) {
		shift_key_state |= MOD_BIT(KC_RSHIFT);
		register_code(KC_RSHIFT);
		send_keyboard_report();		
	    } else {
		shift_key_state &= ~MOD_BIT(KC_RSHIFT);
		unregister_code(KC_RSHIFT);
		send_keyboard_report();		
	    }
	    break;

	// number functions to invert shift modifier
        case SHIFTED_1:
            if (record->event.pressed) {
	        reverse_shift(1, KC_1);
	    } else {
		reverse_shift(0, KC_1);
	    }
	    break;
	case SHIFTED_2:
            if (record->event.pressed) {
	        reverse_shift(1, KC_2);
	    } else {
		reverse_shift(0, KC_2);
	    }
	    break;
	case SHIFTED_3:
            if (record->event.pressed) {
	        reverse_shift(1, KC_3);
	    } else {
		reverse_shift(0, KC_3);
	    }
	    break;
	case SHIFTED_4:
            if (record->event.pressed) {
	        reverse_shift(1, KC_4);
	    } else {
		reverse_shift(0, KC_4);
	    }
	    break;
	case SHIFTED_5:
            if (record->event.pressed) {
	        reverse_shift(1, KC_5);
	    } else {
		reverse_shift(0, KC_5);
	    }
	    break;
	case SHIFTED_6:
            if (record->event.pressed) {
	        reverse_shift(1, KC_6);
	    } else {
		reverse_shift(0, KC_6);
	    }
	    break;
	case SHIFTED_7:
            if (record->event.pressed) {
	        reverse_shift(1, KC_7);
	    } else {
		reverse_shift(0, KC_7);
	    }
	    break;
	case SHIFTED_8:
            if (record->event.pressed) {
	        reverse_shift(1, KC_8);
	    } else {
		reverse_shift(0, KC_8);
	    }
	    break;
	case SHIFTED_9:
            if (record->event.pressed) {
	        reverse_shift(1, KC_9);
	    } else {
		reverse_shift(0, KC_9);
	    }
	    break;
	case SHIFTED_0:
            if (record->event.pressed) {
	        reverse_shift(1, KC_0);
	    } else {
		reverse_shift(0, KC_0);
	    }
	    break;
    }
} 
