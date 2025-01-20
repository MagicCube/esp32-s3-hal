#include "mx_view.h"

MXView::MXView() {}

MXView::~MXView() {
  _subviews.clear();
  _root = nullptr;
}

void MXView::init() {
  if (isInitialized()) {
    return;
  }
  _root = createRoot();
  onInit();
  _initialized = true;
  onLayout();
}

MXObject* MXView::createRoot() {
  auto root = new MXObject(lv_obj_create(lv_scr_act()));
  root->reset_to_default();
  root->size_fit();
  return root;
}

void MXView::update() {
  if (!isInitialized()) {
    init();
  }
  onUpdate();
}

void MXView::addSubview(MXView* subview) {
  subview->_parentView = this;
  _subviews.push_back(subview);
  lv_obj_set_parent(subview->root()->lv_object(), root()->lv_object());
}

void MXView::removeSubview(MXView* subview) {
  subview->_parentView = nullptr;
  _subviews.erase(std::remove(_subviews.begin(), _subviews.end(), subview),
                  _subviews.end());
  lv_obj_set_parent(subview->root()->lv_object(), nullptr);
}
