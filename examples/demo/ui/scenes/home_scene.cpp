#include "home_scene.h"

#ifdef CAM_D0
#include "camera_scene.h"
#endif
#include "select_agent_scene.h"

HomeScene* HomeScene::_instance = nullptr;

LV_IMG_DECLARE(img_home_scene_bg);

AppInfo APP_INFO_LIST[6] = {
    {"call_agent", "通话", "\uf095", rgb(0x31C959)},
#ifdef CAM_D0
    {"camera", "相机", "\uf030", rgb(0x36BC9B)},
#endif
    {"music", "音乐", "\uf001", rgb(0xE64D3D)},
    {"aigc", "绘话", "\ue2ca", rgb(0x4FC0E8)},
    {"studio", "智能体", "\uf4ff", rgb(0xF1C30E)},
    {"settings", "设置", "\uf013", rgb(0xA6AFB6)},
};

void HomeScene::onInit() {
  MXScene::onInit();

  root()->bg_black()->scrollable(true)->scroll_bar_hidden()->scroll_snap_x(
      LV_SCROLL_SNAP_START);

  uint16_t iconCount = sizeof(APP_INFO_LIST) / sizeof(APP_INFO_LIST[0]);
  uint8_t pageCount = (iconCount + 3) / 4;

  appIconsPages = new MXObject*[pageCount];
  uint8_t pageIndex = 0;
  MXObject* appIconsPage = nullptr;
  for (uint16_t i = 0; i < iconCount; i++) {
    if (i % 4 == 0) {
      appIconsPage = root()
                         ->add_object()
                         ->flex(LV_FLEX_FLOW_ROW_WRAP)
                         ->gap(24, 12)
                         ->w_full()
                         ->x(pageIndex * 240)
                         ->y(40)
                         ->p_x(20);
      appIconsPages[pageIndex] = appIconsPage;
      pageIndex++;
    }
    AppInfo& appInfo = APP_INFO_LIST[i];
    MXObject* appIconContainer =
        appIconsPage->add_object()
            ->flex_col(LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER,
                       LV_FLEX_ALIGN_CENTER)
            ->gap(0, 4);
    MXObject* appButton = appIconContainer->add_button(appInfo.icon)
                              ->size(88)
                              ->rounded(20)
                              ->bg(appInfo.color)
                              ->icon_font(48)
                              ->on_click([this, appInfo](MXEvent* e) {
                                this->handleAppButtonClick(appInfo);
                              });
    MXObject* appName = appIconContainer->add_label(appInfo.name);
  }
}

void HomeScene::handleAppButtonClick(const AppInfo& appInfo) {
  if (strcmp(appInfo.id, "call_agent") == 0) {
    SelectAgentScene::instance()->show();
  } else if (strcmp(appInfo.id, "camera") == 0) {
#ifdef CAM_D0
    CameraScene::instance()->show();
#endif
  }
}
