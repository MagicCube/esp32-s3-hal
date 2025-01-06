# esp32-s3-hal

An Arduino version of the hardware abstraction layer for the ESP32-S3.
MXFramework is also built-in.

## Usage

### Add Board

Copy the [`boards/esp32-s3-wroom-1-n16r8`](./boards/esp32-s3-wroom-1-n16r8) file to the `boards` folder under your project.

### Add Library

#### Step 1: Add platform packages

```ini
platform_packages =
  platformio/framework-arduinoespressif32@https://github.com/espressif/arduino-esp32.git
  platformio/framework-arduinoespressif32-libs@https://github.com/espressif/esp32-arduino-libs.git#idf-release/v5.1
```

#### Step 2: Add libraries and dependencies

```ini
lib_deps =
  ESP32_IO_Expander = https://github.com/esp-arduino-libs/ESP32_IO_Expander.git#v0.1.0
  ESP32_Display_Panel = https://github.com/esp-arduino-libs/ESP32_Display_Panel.git#v0.1.8
  esp32-s3-hal = https://github.com/MagicCube/esp32-s3-hal.git
  lvgl/lvgl@~9.2.2
```

#### Step 3: Add build flags

```ini
build_flags =
  -D DEVICE_KEVIN_S3_SP_V3
  ;-D DEVICE_JC3636W518C
  -D LV_CONF_PATH="${platformio.libdeps_dir}/${PIOENV}/include/lv_conf.h"
```

> Notes:
>
> * Choose one of `DEVICE_KEVIN_S3_SP_V3` or `DEVICE_JC3636W518C` to define the device.
> * `LV_CONF_PATH` is used to specify the path to the LVGL configuration file.

### For Multi-Device Support

```ini
; PlatformIO Project Configuration File
;
;   Build options: build flags, source filter
;   Upload options: custom upload port, speed and extra flags
;   Library options: dependencies, extra library storages
;   Advanced options: extra scripting
;
; Please visit documentation for the other options and examples
; https://docs.platformio.org/page/projectconf.html

[platformio]
default_envs = jc3636w518c

[common]
lib_deps =
  lvgl/lvgl@~9.2.2
  esp32-s3-hal = https://github.com/MagicCube/esp32-s3-hal.git
build_flags =
  -D LV_CONF_PATH="${platformio.libdeps_dir}/${PIOENV}/esp32-s3-hal/include/lv_conf.h"

[esp32_s3_wroom_1_n16r8]
platform = espressif32
board = esp32-s3-wroom-1-n16r8
framework = arduino
platform_packages =
  platformio/framework-arduinoespressif32@https://github.com/espressif/arduino-esp32.git
  platformio/framework-arduinoespressif32-libs@https://github.com/espressif/esp32-arduino-libs.git#idf-release/v5.1
build_flags =
  ${common.build_flags}
lib_deps =
  ${common.lib_deps}
  ESP32_IO_Expander = https://github.com/esp-arduino-libs/ESP32_IO_Expander.git#v0.1.0
  ESP32_Display_Panel = https://github.com/esp-arduino-libs/ESP32_Display_Panel.git#v0.1.8

[env:jc3636w518c]
extends= esp32_s3_wroom_1_n16r8
build_flags =
  -D DEVICE_JC3636W518C
  ${esp32_s3_wroom_1_n16r8.build_flags}

[env:kevin_s3_sp_v3]
extends = esp32_s3_wroom_1_n16r8
build_flags =
  -D DEVICE_KEVIN_S3_SP_V3
  ${esp32_s3_wroom_1_n16r8.build_flags}
```

## Example Code

```cpp
#include <Arduino.h>
#include <audio.h>
#include <display.h>
#include <lv_integration.h>
#include <lvgl.h>
#include <mx.h>

void hal_setup() {
  Serial.begin(115200);
  Audio.begin();
  Audio.playSystemSound(SYSTEM_SOUND_STARTUP);
  Display.begin();
#ifdef DISPLAY_ST77916
  Display.rotate(180);
#endif
}

void setup() {
  hal_setup();
  lv_setup();
}

time_t last_serial_output = 0;
void serial_loop() {
  if (millis() - last_serial_output > 5 * 1000) {
    // Serial.print(".");
    // Print free memory
    Serial.print("Free memory: ");
    Serial.println(esp_get_free_heap_size());

    last_serial_output = millis();
  }
}

void loop() {
  serial_loop();
  mx_loop();

  // Always keep `lv_loop()` at the end of the loop
  lv_loop();
}
```
