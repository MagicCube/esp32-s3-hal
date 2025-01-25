#include "home_scene.h"

#include "select_agent_scene.h"

HomeScene* HomeScene::_instance = nullptr;

LV_IMG_DECLARE(img_home_scene_bg);

AppInfo APP_INFO_LIST[4] = {
    {"select_agent_scene", "通话", "\uf095", rgb(0x31C959)},
    {"camera_scene", "相机", "\uf030", rgb(0x36BC9B)},
    {"music_scene", "音乐", "\uf001", rgb(0xE64D3D)},
    {"settings_scene", "设置", "\uf013", rgb(0xA6AFB6)},
};

void HomeScene::onInit() {
  MXScene::onInit();

  root()->bg_black();

  appIconsContainer = root()
                          ->add_object()
                          ->flex(LV_FLEX_FLOW_ROW_WRAP)
                          ->gap(32, 12)
                          ->p_x(16)
                          ->w_full()
                          ->y(40)
                          ->scrollable(true)
                          ->scroll_bar_hidden();
  uint16_t count = sizeof(APP_INFO_LIST) / sizeof(APP_INFO_LIST[0]);
  for (uint16_t i = 0; i < count; i++) {
    AppInfo& appInfo = APP_INFO_LIST[i];
    MXObject* appIconContainer =
        appIconsContainer->add_object()
            ->flex_col(LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER,
                       LV_FLEX_ALIGN_CENTER)
            ->gap(0, 4);
    MXObject* appIcon = appIconContainer->add_button(appInfo.icon)
                            ->size(88)
                            ->rounded(20)
                            ->bg(appInfo.color)
                            ->icon_font(48);
    MXObject* appName = appIconContainer->add_label(appInfo.name);
  }
}
