#include "camera.h"

#include "display.h"
#include "pin_conf.h"

void CameraClass::begin() {
  camera_config_t camera_config = {
      .pin_pwdn = CAM_PWDN,
      .pin_reset = CAM_RESET,
      .pin_xclk = CAM_XCLK,
      .pin_sscb_sda = CAM_SIOD,
      .pin_sscb_scl = CAM_SIOC,

      .pin_d7 = CAM_D7,
      .pin_d6 = CAM_D6,
      .pin_d5 = CAM_D5,
      .pin_d4 = CAM_D4,
      .pin_d3 = CAM_D3,
      .pin_d2 = CAM_D2,
      .pin_d1 = CAM_D1,
      .pin_d0 = CAM_D0,
      .pin_vsync = CAM_VSYNC,
      .pin_href = CAM_HREF,
      .pin_pclk = CAM_PCLK,

      .xclk_freq_hz = 20 * 1000 * 1000,  // 10MHz, XCLK frequency
      .ledc_timer = LEDC_TIMER_0,
      .ledc_channel = LEDC_CHANNEL_0,
      .pixel_format = PIXFORMAT_RGB565,   // Pixel format
      .frame_size = FRAMESIZE_240X240,    // Frame size
      .jpeg_quality = 12,                 // JPEG quality (0-63)
      .fb_count = 2,                      // Frame buffer count
      .fb_location = CAMERA_FB_IN_PSRAM,  // Frame buffer in PSRAM
      .grab_mode = camera_grab_mode_t::CAMERA_GRAB_WHEN_EMPTY};

  if (esp_camera_init(&camera_config) != ESP_OK) {
    Serial.println("Camera init failed!");
    return;
  }

  // Access the camera sensor
  sensor_t *s = esp_camera_sensor_get();
  if (s) {
    s->set_vflip(s, 1);    // Vertical flip
    s->set_hmirror(s, 0);  // Horizontal mirror
  }

  _initialized = true;
}

void CameraClass::update() {
  if (!initialized() || !isLiveViewing()) {
    return;
  }

  if (millis() - _lastUpdateTime < 1000 / fps()) {
    return;
  }
  _lastUpdateTime = millis();

  camera_fb_t *fb = esp_camera_fb_get();
  if (fb == nullptr) {
    Serial.println("Camera capture failed");
    return;
  }
  uint8_t *bitmap = (uint8_t *)fb->buf;
  Display.drawBitmap(bitmap, (Display.width() - fb->width) / 2, -1, fb->width,
                     fb->height);
  esp_camera_fb_return(fb);
  fb = nullptr;
}

void CameraClass::end() {
  stopLiveView();
  esp_camera_deinit();
  _initialized = false;
}

void CameraClass::startLiveView() { _liveViewing = true; }

void CameraClass::stopLiveView() { _liveViewing = false; }

CameraClass Camera;
