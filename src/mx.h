#pragma once

#include "mx/mx_application.h"
#include "mx/mx_color.h"
#include "mx/mx_event.h"
#include "mx/mx_font.h"
#include "mx/mx_object.h"
#include "mx/mx_scene.h"
#include "mx/mx_view.h"

inline void preload() { mx_preload_fonts(); }

inline void mx_setup() {
  preload();
  MXApplication::init();
  MXApplication::start();
}

inline void mx_loop() { MXApplication::update(); }
