#include "mx_application.h"

MXApplication* MXApplication::_instance = nullptr;

MXApplication::MXApplication() { _instance = this; }

MXApplication* MXApplication::instance() { return _instance; }

void MXApplication::init() { onInit(); }

void MXApplication::start() { onStart(); }

void MXApplication::update() { onUpdate(); }
