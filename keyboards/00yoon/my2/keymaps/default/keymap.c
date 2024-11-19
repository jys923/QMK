// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "print.h"
#include "raw_hid.h"

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
    [0] = LAYOUT_numpad_2x4(
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
    //debug_enable = true;
    //debug_matrix = true;
    //debug_keyboard = true;
    //debug_mouse = true;
    //serial_init();
    //serial_flush();
    rgblight_setrgb(0, 0, 0);
}

void matrix_init_user(void) { 
    //rgblight_setrgb(0, 0, 0);
}

// void matrix_scan_user(void) {

// }

void turn_off_all_leds(void) {
    for (uint8_t i = 0; i < 4; i++) {
        rgblight_setrgb_at(0, 0, 0, i);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool result = true; // 기본 리턴 값 설정

#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif 

    switch (keycode) {
        case CTRL_C:
            if (record->event.pressed) {
                tap_code16(C(KC_C));
            }
            result = false;
            break;
        case CTRL_V:
            if (record->event.pressed) {
                tap_code16(C(KC_V));
            }
            result = false;
            break;
        case D_3:
            if (record->event.pressed) {
                tap_code16(C(KC_F3));
                turn_off_all_leds();
                rgblight_setrgb_at(255, 0, 0, 0);
            }
            result = false;
            break;
        case D_4:
            if (record->event.pressed) {
                tap_code16(C(KC_F4));
                turn_off_all_leds();
                rgblight_setrgb_at(255, 0, 0, 1);
            }
            result = false;
            break;
        case D_5:
            if (record->event.pressed) {
                tap_code16(C(KC_F5));
                turn_off_all_leds();
                rgblight_setrgb_at(255, 0, 0, 2);
            }
            result = false;
            break;
        case D_6:
            if (record->event.pressed) {
                tap_code16(C(KC_F6));
                turn_off_all_leds();
                rgblight_setrgb_at(255, 0, 0, 3);
            }
            result = false;
            break;
        case KC_F10:
            if (record->event.pressed) {
                bool current_state = get_led_state(4);
                if (current_state) {
                    update_led_state(0, 0, 0, 4);
                } else {
                    update_led_state(0, 255, 0, 4);
                }
            } else {
                tap_code(KC_F10);
            }
            result = false;
            break;
        case QK_MOUSE_BUTTON_1:
            if (record->event.pressed) {
                rgblight_setrgb_at(0, 0, 255, 5);
            } else {
                tap_code(QK_MOUSE_BUTTON_1);
                rgblight_setrgb_at(0, 0, 0, 5);
            }
            result = false;
            break;
        case QK_MOUSE_BUTTON_2:
            if (record->event.pressed) {
                rgblight_setrgb_at(0, 0, 255, 6);
            } else {
                tap_code(QK_MOUSE_BUTTON_2);
                rgblight_setrgb_at(0, 0, 0, 6);
            }
            result = false;
            break;
        case KC_F11:
            if (record->event.pressed) {
                rgblight_setrgb_at(0, 255, 0, 7);
            } else {
                tap_code(KC_F11);
                rgblight_setrgb_at(0, 0, 0, 7);
            }
            result = false;
            break;
        default:
            result = true;
            break;
    }
    return result;
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

// led_state 배열 값을 사용하여 RGB 조명을 설정하는 함수
void update_leds_based_on_state(bool led_state[], uint8_t length) {
    for (uint8_t i = 0; i < length; i++) {
        if (led_state[i]) {
            rgblight_setrgb_at(255, 0, 0, i); // 예: LED 켜기 (빨강색)
        } else {
            rgblight_setrgb_at(0, 0, 0, i); // 예: LED 끄기
        }
    }
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
    uprintf("raw_hid_receive!\n");

    // 받은 데이터 출력
    for (uint8_t i = 0; i < length; i++) {
        uprintf("%02X ", data[i]);
    }
    uprintf("\n");

    // 받은 데이터를 뒤집어서 응답 데이터 생성
    uint8_t response[length];
    for (uint8_t i = 0; i < length; i++) {
        response[i] = data[length - 1 - i];
    }

    // 뒤집어진 데이터 출력
    uprintf("response data:\n");
    for (uint8_t i = 0; i < length; i++) {
        uprintf("%02X ", response[i]);
    }
    uprintf("\n");

    // 뒤집어진 데이터 전송
    raw_hid_send(response, length);

    // 받은 데이터를 led_state 배열에 설정
    for (uint8_t i = 0; i < 10 && i < length; i++) {
        led_state[i] = data[i] ? true : false;
    }

    // led_state 배열 값에 따라 RGB 조명 설정
    update_leds_based_on_state(led_state, 10);
}


void housekeeping_task_user(void) {
    check_and_turn_off_leds(8);
    check_and_turn_off_leds(9);
}