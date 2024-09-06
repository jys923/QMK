// config.h
#include QMK_KEYBOARD_H

#ifndef CONFIG_H
#define CONFIG_H

#define ENCODER_COUNT 6
#define ENCODER_A_PINS { GP9, GP11, GP13, GP20, GP22, GP27 }
#define ENCODER_B_PINS { GP10, GP12, GP14, GP21, GP26, GP28 }

// SPI 설정을 활성화합니다
// #define USE_SPI
// #define SPI_CLOCK_DIV2  // SPI 클럭 설정, 필요한 경우 수정하세요

#define SPI_DRIVER_ENABLE
#define SPI_DRIVER_DEFAULT_TYPE 1  // SPI 트랙볼 드라이버 타입에 따라 다를 수 있음

#endif // CONFIG_H
