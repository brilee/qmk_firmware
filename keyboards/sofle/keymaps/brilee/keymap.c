#include QMK_KEYBOARD_H

enum custom_keycodes {
    KC_MACRO_LARROW = SAFE_RANGE,
    KC_MACRO_RARROW,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        // Basic Dvorak with slight mods
        [0] = LAYOUT(
            KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
            KC_TAB, KC_QUOT, KC_COMM, KC_DOT, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, KC_DEL,
            KC_LCTL, KC_A, KC_O, KC_E, KC_U, KC_I, KC_D, KC_H, KC_T, KC_N, KC_S, KC_ENT,
            KC_LSFT, KC_SLSH, KC_Q, KC_J, KC_K, KC_X, KC_NO, KC_NO, KC_B, KC_M, KC_W, KC_V, KC_Z, KC_RSFT,
            LSFT(KC_LCTRL), KC_LALT, MO(1), MO(2), MO(3), KC_LGUI, KC_SPC, MO(1), KC_NO, KC_NO
        ),
        // Symbols layer
        [1] = LAYOUT(
            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
            KC_TILD, KC_GRV, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LCBR, KC_RCBR, KC_SLSH, KC_PIPE, KC_BSLS,
            KC_LCTL, KC_PLUS, KC_EQL, KC_MACRO_LARROW, KC_MACRO_RARROW, KC_NO, KC_NO, KC_LPRN, KC_RPRN, KC_COLN, KC_SCLN, KC_ENT,
            KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LBRC, KC_RBRC, KC_MINS, KC_UNDS, KC_RSFT,
            KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_SPC, KC_TRNS, KC_NO, KC_NO
        ),
        // Web nav
        [2] = LAYOUT(
            KC_NO, LCTL(KC_1), LCTL(KC_2), LCTL(KC_3), LCTL(KC_4), LCTL(KC_5), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
            LCTL(KC_TAB), LALT(KC_LEFT), LCTL(KC_W), KC_HOME, KC_END, LCTL(KC_R), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
            LSFT(LCTL(KC_TAB)), KC_NO, KC_NO, KC_PGUP, KC_PGDN, LCTL(KC_T), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
            KC_LSFT, LCTL(KC_L), KC_NO, LCTL(KC_C), LCTL(KC_V), LCTL(KC_N), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_RSFT,
            KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_SPC, KC_TRNS, KC_NO, KC_NO
        ),
        // Editor hotkeys
        [3] = LAYOUT(
            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
            KC_NO, LCTL(KC_A), KC_NO, KC_UP, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
            KC_NO, LCTL(KC_LEFT), KC_LEFT, KC_DOWN, KC_RIGHT, LCTL(KC_RIGHT), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
            KC_LSFT, LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), LCTL(KC_K), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_RSFT,
            KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_SPC, KC_TRNS, KC_NO, KC_NO
        )   
};
#ifdef OLED_ENABLE

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0
    };

    oled_write_P(qmk_logo, false);
}

static void print_status_narrow(void) {
    oled_write_P(PSTR("\n\n"), false);
    // Print current layer
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case 1:
            oled_write_P(PSTR("Symbol\n"), false);
            break;
        case 2:
            oled_write_P(PSTR("WebNav\n"), false);
            break;
        case 3:
            oled_write_P(PSTR("Edit\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }
    return false;
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_MACRO_LARROW:
            if (record->event.pressed) {
                SEND_STRING(SS_LSFT(SS_TAP(X_COMMA)) SS_DELAY(10) SS_TAP(X_MINUS));
            }
            break;
        case KC_MACRO_RARROW:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_MINUS) SS_DELAY(10) SS_LSFT(SS_TAP(X_DOT)));
            }
            break;
    }
    return true;
}

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    // my encoders are installed backwards so the CW/CCW are swapped.
    if (index == 0) {
        if (clockwise) {
            SEND_STRING(SS_LCTL(SS_TAP(X_MINS)));
        } else {
            SEND_STRING(SS_LCTL(SS_TAP(X_EQL)));
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    }
    return true;
}

#endif
