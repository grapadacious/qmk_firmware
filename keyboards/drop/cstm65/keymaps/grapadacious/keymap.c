// Copyright 2023 Massdrop, Inc.
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

static int current_layer = 0;
static bool is_caps = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_65_ansi_blocker(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,
        KC_CAPS ,KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN,
        KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                             KC_RGUI, MO(1),   KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT_65_ansi_blocker(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_MUTE,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MEDIA_PLAY_PAUSE, 
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, KC_VOLU,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, KC_VOLD,
        MO(2),   _______, _______,                            EE_CLR,                             _______, _______, KC_MPRV, _______, KC_MNXT
    ),
    [2] = LAYOUT_65_ansi_blocker(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______
    )
};

void set_lights(void) {
    if (is_caps) {
        rgblight_sethsv_noeeprom(HSV_RED);
        rgblight_mode_noeeprom(RGB_MATRIX_RAINBOW_PINWHEELS);
        return;
    }

    if (current_layer == 1) {
        rgblight_sethsv_noeeprom(HSV_GREEN);
        rgblight_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
        return;
    }

    if (current_layer == 2) {
        rgblight_sethsv_noeeprom(HSV_BLUE);
        rgblight_mode_noeeprom(RGB_MATRIX_BREATHING);
        return;
    }

    rgblight_sethsv_noeeprom(HSV_WHITE);
    rgblight_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    current_layer = get_highest_layer(state);
    set_lights();
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_CAPS:
            if (record->event.pressed) {
                is_caps = !is_caps;
            }
            set_lights();
            return true;
        case MO(1):
        case MO(2):
            return !is_caps;
        default:
            return true;
    }
}

void keyboard_post_init_user(void) {
    rgblight_enable();
    rgblight_sethsv(HSV_WHITE);
    rgblight_mode(RGB_MATRIX_SOLID_COLOR);
}
