#pragma once

class MXApplication {
 public:
  MXApplication();

  static MXApplication* instance();

  void init();
  void start();
  void update();

 protected:
  inline virtual void onInit() {};
  inline virtual void onStart() {};
  inline virtual void onUpdate() {};

 private:
  static MXApplication* _instance;
};
