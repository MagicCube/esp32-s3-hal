#include "mx_view.h"

void MXView::begin() {
  if (isInitialized()) {
    return;
  }
  onInit();
  _initialized = true;
  onLayout();
}

MXView::~MXView() {
  if (_root) {
    delete _root;
    _root = nullptr;
  }
}

MXObject *MXView::createRoot() {
  MXObject *root = mx();
  return root;
}

int32_t MXView::width() const { return lv_obj_get_width(root()->lv_object()); }

int32_t MXView::height() const {
  return lv_obj_get_height(root()->lv_object());
}

void MXView::onInit() { _root = createRoot(); }

void MXView::update() { onUpdate(); }
