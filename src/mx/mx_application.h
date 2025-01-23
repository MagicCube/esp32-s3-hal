#pragma once

class MXApplication {
 public:
  void init() { onInit(); };

  void start() { onStart(); };

  void update() { onUpdate(); };

 protected:
  inline virtual void onInit() {};
  inline virtual void onStart() {};
  inline virtual void onUpdate() {};
};
