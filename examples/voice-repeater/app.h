#pragma once

#include <Arduino.h>
#include <lvgl.h>
#include <mx.h>

#include "main_scene.h"

MainScene mainScene;
inline void app_main() { mainScene.show(); }
