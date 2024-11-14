// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "print.h"

// LED 상태를 저장할 배열
bool led_state[RGBLIGHT_LED_COUNT] = {false};
// LED 타이머 배열
uint16_t led_timer[RGBLIGHT_LED_COUNT] = {0};

bool get_led_state(uint8_t index) {
    return led_state[index];
}

void update_led_state(uint8_t r, uint8_t g, uint8_t b,uint8_t index) {
    // LED 상태 저장
    if (r > 0 || g > 0 || b > 0) {
        led_state[index] = true;
    } else {
        led_state[index] = false;
    }
    // LED 색상 설정
    rgblight_setrgb_at(r, g, b, index);
}

void check_and_turn_off_leds(uint8_t index) {
    if (led_state[index] && timer_elapsed(led_timer[index]) > 500) { // 500ms 후에 LED 끄기
        update_led_state(0, 0, 0,index);
    }
}

// 일정 시간 후에 LED를 끄는 함수
void turn_off_led_after_delay(uint16_t delay, uint8_t index) {
    wait_ms(delay);
    update_led_state(0, 0, 0,index);
}

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
     * │ 1 │ 2 │ 3 │   │
     * └───┴───┴───┴───┘
     */
    [0] = LAYOUT_numpad_5x4(
        D_3,  D_4,  D_5,   D_6,
        KC_F10,  QK_MOUSE_BUTTON_1,   QK_MOUSE_BUTTON_2,   KC_F11
    ),
};

// bool rgb_matrix_indicators_kb(void) {
// }

// void keyboard_pre_init_user(void) {
// }

void keyboard_post_init_user(void) {
    #ifdef CONSOLE_ENABLE
        uprintf("keyboard_pre_init_user!\n");
    #endif 
    debug_enable = true;
    debug_matrix = true;
    //debug_mouse = true;

    for (uint8_t i = 0; i < RGBLIGHT_LED_COUNT; i++) { 
        rgblight_setrgb_at(0, 0, 0, i); 
    } 
}

// void matrix_init_user(void) { 
// }

// void matrix_scan_user(void) {

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
                register_code(KC_LCTL);
                tap_code(KC_F3);
                for (uint8_t i = 0; i < 4; i++) {
                    if (i == 0) {
                        rgblight_setrgb_at(255, 0, 0, i); // 키가 눌렸을 때 해당 LED 켜기
                    } else {
                        rgblight_setrgb_at(0, 0, 0, i); // 나머지 LED 끄기
                    }
                }
            } else {
                unregister_code(KC_LCTL);
            }
            return false;
            break;
        case D_4:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_F4);
                for (uint8_t i = 0; i < 4; i++) {
                    if (i == 1) {
                        rgblight_setrgb_at(255, 0, 0, i); // 키가 눌렸을 때 해당 LED 켜기
                    } else {
                        rgblight_setrgb_at(0, 0, 0, i); // 나머지 LED 끄기
                    }
                }
            } else {
                unregister_code(KC_LCTL);
            }
            return false;
            break;
        case D_5:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_F5);
                for (uint8_t i = 0; i < 4; i++) {
                    if (i == 2) {
                        rgblight_setrgb_at(255, 0, 0, i); // 키가 눌렸을 때 해당 LED 켜기
                    } else {
                        rgblight_setrgb_at(0, 0, 0, i); // 나머지 LED 끄기
                    }
                }
            } else {
                unregister_code(KC_LCTL);
            }
            return false;
            break;
        case D_6:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_F6);
                for (uint8_t i = 0; i < 4; i++) {
                    if (i == 3) {
                        rgblight_setrgb_at(255, 0, 0, i); // 키가 눌렸을 때 해당 LED 켜기
                    } else {
                        rgblight_setrgb_at(0, 0, 0, i); // 나머지 LED 끄기
                    }
                }
            } else {
                unregister_code(KC_LCTL);
            }
            return false;
            break;
        case KC_F10:
            if (record->event.pressed) {
                bool current_state = get_led_state(4);
                if (current_state) {
                    update_led_state(0, 0, 0, 4);  // LED 끄기
                } else {
                    update_led_state(0, 255, 0, 4);  // LED 켜기 (빨간색)
                }
            } else {
                tap_code(KC_F10);
            }
            return false;
            break;
        case QK_MOUSE_BUTTON_1:
            if (record->event.pressed) {
                rgblight_setrgb_at(0, 0, 255, 5);
            } else {
                tap_code(QK_MOUSE_BUTTON_1);
                rgblight_setrgb_at(0, 0, 0, 5);
            }
            return false;
            break;
        case QK_MOUSE_BUTTON_2:
            if (record->event.pressed) {
                rgblight_setrgb_at(0, 0, 255, 6);
            } else {
                tap_code(QK_MOUSE_BUTTON_2);
                rgblight_setrgb_at(0, 0, 0, 6);
            }
            return false;
            break;
        case KC_F11:
            if (record->event.pressed) {
                rgblight_setrgb_at(0, 255, 0, 7);
            } else {
                tap_code(KC_F11);
                rgblight_setrgb_at(0, 0, 0, 7);
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
        default:
            return true;
    }
    return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            register_code(KC_LCTL);
            tap_code(KC_F9);
            unregister_code(KC_LCTL);
            update_led_state(255, 255, 0, 8);
        } else {
            register_code(KC_LSFT);
            tap_code(KC_F9);
            unregister_code(KC_LSFT);
            update_led_state(0, 255, 255, 8);
        }
        //turn_off_led_after_delay(500, 8);
        led_timer[8] = timer_read(); // 타이머 리셋
    } else 
    if (index == 2) { /* Second encoder */
        if (clockwise) {
            register_code(KC_LCTL);
            tap_code(KC_F12);
            unregister_code(KC_LCTL);
            update_led_state(255, 255, 0, 9);
        } else {
            register_code(KC_LSFT);
            tap_code(KC_F12);
            unregister_code(KC_LSFT);
            update_led_state(0, 255, 255, 9);
        }
        //turn_off_led_after_delay(500, 9);
        led_timer[9] = timer_read(); // 타이머 리셋
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

void housekeeping_task_user(void) {
    check_and_turn_off_leds(8);
    check_and_turn_off_leds(9);
}