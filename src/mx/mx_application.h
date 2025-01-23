#pragma once

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
  inline virtual void onInit() {};
  inline virtual void onStart() {};
  inline virtual void onUpdate() {};

 private:
  static MXApplication* _instance;
  static MXScene* _activeScene;
};
