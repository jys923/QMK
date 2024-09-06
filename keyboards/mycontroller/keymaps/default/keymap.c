// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "spi.h"
#include "mouse.h"

// SPI 트랙볼의 핀 설정
#define SPI_CS_PIN GP17
#define SPI_CLK_PIN GP18
#define SPI_MOSI_PIN GP19
#define SPI_MISO_PIN GP20

void matrix_init_user(void) {
    // SPI 초기화
    spi_init(SPI_CS_PIN, SPI_CLK_PIN, SPI_MOSI_PIN, SPI_MISO_PIN);
}

void matrix_scan_user(void) {
    // SPI 트랙볼에서 데이터를 읽고 마우스 이동 처리
    uint16_t x, y;
    spi_read_trajectory(&x, &y);
    mouse_move(x, y);
}

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
        TG(1),   KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,
        KC_P0,   KC_PDOT,          KC_PENT
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
    [1] = LAYOUT_numpad_5x4(
        _______, _______, _______, _______,
        KC_HOME, KC_UP,   KC_PGUP,
        KC_LEFT, XXXXXXX, KC_RGHT, _______,
        KC_END,  KC_DOWN, KC_PGDN,
        KC_INS,           KC_DEL,  _______
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),      ENCODER_CCW_CW(KC_VOLD, KC_VOLU),      ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [1] =  { ENCODER_CCW_CW(KC_TRNS, KC_TRNS),      ENCODER_CCW_CW(KC_TRNS, KC_TRNS),      ENCODER_CCW_CW(KC_TRNS, KC_TRNS)  },
    [2] =  { ENCODER_CCW_CW(KC_TRNS, KC_TRNS),      ENCODER_CCW_CW(KC_TRNS, KC_TRNS),      ENCODER_CCW_CW(KC_TRNS, KC_TRNS)  },
    [3] =  { ENCODER_CCW_CW(KC_TRNS, KC_TRNS),      ENCODER_CCW_CW(KC_TRNS, KC_TRNS),      ENCODER_CCW_CW(KC_TRNS, KC_TRNS)  }
};
#endif
