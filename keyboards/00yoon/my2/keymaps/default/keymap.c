// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "print.h"

enum custom_keycodes {
    CTRL_C = SAFE_RANGE,
    CTRL_V,
    D_3,
    D_4,
    D_5,
    D_6,
    G_PLUS,
    G_MINUS,
    R_PLUS,
    R_MINUS,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │TG1│ / │ * │ - │
     * ├───┼───┼───┼───┤
     * │ 7 │ 8 │ 9 │   │
     * ├───┼───┼───┤ + │
     * │ 4 │ 5 │ 6 │   │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │   │
     * ├───┴───┼───┤Ent│
     * │   0   │ . │   │
     * └───────┴───┴───┘
     */
    [0] = LAYOUT_numpad_5x4(
        D_3,  D_4,  D_5,   D_6,
        KC_F10,  QK_MOUSE_BUTTON_1,   QK_MOUSE_BUTTON_2,   KC_F11
    ),

    /*
     * ┌───┬───┬───┬───┐
     * │TG1│ / │ * │ - │
     * ┌───┬───┬───┐───┤
     * │Hom│ ↑ │PgU│   │
     * ├───┼───┼───┤ + │
     * │ ← │   │ → │   │
     * ├───┼───┼───┤───┤
     * │End│ ↓ │PgD│   │
     * ├───┴───┼───┤Ent│
     * │Insert │Del│   │
     * └───────┴───┘───┘
     */
};

void keyboard_post_init_user(void) {
    debug_enable = true;
    debug_matrix = true;
    debug_mouse = true;
}

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//   // If console is enabled, it will print the matrix position and status of each key pressed
// #ifdef CONSOLE_ENABLE
//     uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
// #endif 
//   return true;
// }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif 
    switch (keycode) {
        case CTRL_C:
            if (record->event.pressed) {
                // Ctrl + C 누르기
                register_code(KC_LCTL);
                tap_code(KC_C);
            } else {
                // Ctrl + C 떼기
                unregister_code(KC_LCTL);
            }
            return false;
            break;
        case CTRL_V:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_V);
            } else {
                unregister_code(KC_LCTL);
            }
            return false;
            break;
        case D_3:
            if (record->event.pressed) {
                register_code(KC_D);
                tap_code(KC_3);
            } else {
                unregister_code(KC_D);
            }
            return false;
            break;
        case D_4:
            if (record->event.pressed) {
                register_code(KC_D);
                tap_code(KC_4);
            } else {
                unregister_code(KC_D);
            }
            return false;
            break;
        case D_5:
            if (record->event.pressed) {
                register_code(KC_D);
                tap_code(KC_5);
            } else {
                unregister_code(KC_D);
            }
            return false;
            break;
        case D_6:
            if (record->event.pressed) {
                register_code(KC_D);
                tap_code(KC_6);
            } else {
                unregister_code(KC_D);
            }
            return false;
            break;
        case G_PLUS:
            if (record->event.pressed) {
                register_code(KC_G);
                tap_code(KC_EQUAL);
            } else {
                unregister_code(KC_G);
            }
            return false;
            break;
        case G_MINUS:
            if (record->event.pressed){
                register_code(KC_G);
                tap_code(KC_MINUS);
            } else {
                unregister_code(KC_G);
            }
            return false;
            break;
        case R_PLUS:
            if (record->event.pressed){
                register_code(KC_R);
                tap_code(KC_EQUAL);
            } else {
                unregister_code(KC_R);
            }
            return false;
            break;
        case R_MINUS:
            if (record->event.pressed){
                register_code(KC_R);
                tap_code(KC_MINUS);
            } else {
                unregister_code(KC_R);
            }
            return false;
            break;
    }
    return true;
}

bool process_mouse(report_mouse_t *mouse_report) {
#ifdef CONSOLE_ENABLE
    uprintf("Mouse X: %d, Y: %d, V: %d, H: %d\n", 
            mouse_report->x, mouse_report->y, 
            mouse_report->v, mouse_report->h);
#endif             
    return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            register_code(KC_G);
            tap_code(KC_EQUAL);
            unregister_code(KC_G);
        } else {
            register_code(KC_G);
            tap_code(KC_MINUS);
            unregister_code(KC_G);
        }
    } else 
    if (index == 2) { /* Second encoder */
        if (clockwise) {
            register_code(KC_R);
            tap_code(KC_EQUAL);
            unregister_code(KC_R);
        } else {
            register_code(KC_R);
            tap_code(KC_MINUS);
            unregister_code(KC_R);
        }
    } else 
    if (index == 1) { /* Third encoder */
        if (clockwise) {
            tap_code(QK_MOUSE_WHEEL_DOWN);
        } else {
            tap_code(QK_MOUSE_WHEEL_UP);
        }
    }
    return false;
}