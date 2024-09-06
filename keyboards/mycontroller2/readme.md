# mycontroller2

![mycontroller2](imgur.com image replace me!)

*A short description of the keyboard/project*

* Keyboard Maintainer: [yoon](https://github.com/jys923)
* Hardware Supported: *The PCBs, controllers supported*
* Hardware Availability: *Links to where you can find this hardware*

Make example for this keyboard (after setting up your build environment):

    make mycontroller2:default

Flashing example for this keyboard:

    make mycontroller2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

## Todo
track ball, encoder*5, key*4
spi PAW 3204 드라이버 미지원
spi PMW 3360 지원 이걸로 하자
포인팅 디바이스 설정만으로 불가
hal로 gp핀 번호 설정까지
로터리, 키 매드릭스 부터 확인

momo
I want to make a controller with 4 buttons, 5 knobs, and a trackball. First of all, Start track ball. I purchased a PAW 3805 sensor module that communicates with SPI. I tested it by connecting it to a raspberry pi pico via qmk, but it doesn't work. The official document only lists PAW 3204. They say there is a spi driver here. I have coding experience, but no firmware or embedded experience. Should I try purchasing Pimoroni (I2C) or PMW 3360 (spi)? I thought the SPI would be the same anyway, but isn't it?
SPI 핀 연결 예시 
GND → 공통 접지 
MOT (MOSI) → 마스터의 MOSI 핀 
NCS (CS) → 마스터의 CS 핀 (슬레이브 장치의 선택 핀) 
SCLK → 마스터의 SCK 핀 
SDIO → 마스터의 MISO 핀 (데이터 수신용, 필요에 따라 MISO와 SDIO가 같은 핀일 수 있음) 
VDD → 장치의 전원 공급 핀 
MISO (Master In Slave Out): 슬레이브 장치에서 마스터 장치로 데이터를 보내는 핀입니다. 라즈베리파이의 SPI0 RX 핀에 연결됩니다. 
MOSI (Master Out Slave In): 마스터 장치에서 슬레이브 장치로 데이터를 보내는 핀입니다. 라즈베리파이의 SPI0 TX 핀에 연결됩니다.

https://github.com/qmk/qmk_firmware/blob/master/keyboards/oddball/readme.md