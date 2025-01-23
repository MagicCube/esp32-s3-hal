#pragma once

class MXView;
class MXScene;

class MXApplication {
 public:
  MXApplication();

  inline static MXApplication* instance() { return _instance; }

  inline static MXScene* activeScene() { return _activeScene; }

  static void init();
  static void start();
  static void update();

  static void activateScene(MXScene* scene);

 protected:
  MXView* statusBar;

  inline virtual void onInit() {};
  inline virtual void onStart() {};
  inline virtual void onUpdate() {};
  inline virtual void onSceneActivated(MXScene* scene) {};

 private:
  static MXApplication* _instance;
  static MXScene* _activeScene;
};
