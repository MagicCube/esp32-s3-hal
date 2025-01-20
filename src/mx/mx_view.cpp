#include "mx_view.h"

MXView::MXView() {}

MXView::~MXView() {}

void MXView::init() {
  if (isInitialized()) {
    return;
  }
  onInit();
  _initialized = true;
  onLayout();
}

MXObject* MXView::createRoot() {
  auto root = new MXObject();
  root->size_full()->pos(0, 0);
  return root;
}
