#pragma once

// #define CONSOLE_ENABLE
// #define COMMAND_ENABLE

// Spi 설정
// #define USE_SPI
// #define SPI_DRIVER SPID2
#define SPI_SCK_PIN GP18
#define SPI_MOSI_PIN GP19
#define SPI_MISO_PIN GP16
#define PMW33XX_CS_PIN GP17 // SPI CS pin.

/* Optional. */
#define PMW33XX_CPI 1600      // The CPI range is 100-12000, in increments of 100. Defaults to 1600 CPI.
#define PMW33XX_CLOCK_SPEED 2000000 // Sets the clock speed that the sensor runs at. Defaults to 2000000
#define MOUSE_EXTENDED_REPORT // Use -32767 to 32767, instead of just -127 to 127.
// #define POINTING_DEVICE_TASK_THROTTLE_MS 10
#define POINTING_DEVICE_INVERT_Y

/* RP2040 Reset. */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U // Timeout window in ms in which the double tap can occur.
//#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25 // Specify a optional status led by GPIO number which blinks when entering the bootloader

// I2C 설정
// #define USE_I2C
// #define I2C_DRIVER I2CD0
// #define I2C1_SDA_PIN   GP4
// #define I2C1_SCL_PIN   GP5

//#define POINTING_DEVICE_DEBUG
#define ENCODER_RESOLUTION 2

// #define I2C1_SCL_PIN   GP5
// #define I2C1_SDA_PIN   GP4

// //포인팅 장치 설정
// #define PIMORONI_TRACKBALL_ADDRESS
// #define POINTING_DEVICE_ENABLE
// #define POINTING_DEVICE_ROTARY_ENCODER

// #define ENCODER_A_PINS { GP27, GP22, GP20 }
// #define ENCODER_B_PINS { GP28, GP26, GP21 }

// #define MATRIX_ROWS 1
// #define MATRIX_COLS 4

// #define MATRIX_ROW_PINS { GP6 }
// #define MATRIX_COL_PINS { GP2, GP3, GP4, GP5 }

// #define DIODE_DIRECTION COL2ROW

#define WS2812_PIO_USE_PIO2
#define WS2812_DI_PIN GP14 //GP15
//#define WS2812_LED_COUNT 10
#define RGBLIGHT_LED_COUNT 20

//#define RGBLIGHT_LED_MAP { 0, 1, 2, 3, 7, 6, 5, 4, 8, 9}    

// #define DEBUG_ENABLE
// #define DEBUG_PORT USB_SERIAL_PORT

// #define SERIAL_PIO_USE_PIO1
// #define SERIAL_USART_FULL_DUPLEX
// #define SERIAL_USART_TX_PIN GP12
// #define SERIAL_USART_RX_PIN GP13

// #define RAW_USAGE_PAGE 0xFF60
// #define RAW_USAGE_ID 0x61