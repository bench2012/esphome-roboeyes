#pragma once
#include "esphome.h"

namespace esphome {
namespace roboeyes {

class RoboEyes : public Component {
 public:
  RoboEyes(display::DisplayBuffer *disp) : display_(disp) {}

  void setup() override {
    blink_ = false;
    pupil_x_ = 32;
    pupil_y_ = 32;
    pupil_radius_ = 6;
    blink_timer_ = 0;
  }

  void loop() override {
    // Simple blink timer
    blink_timer_++;
    if (blink_timer_ > 200) {
      blink_ = !blink_;
      blink_timer_ = 0;
    }
  }

  void draw() {
    // sclera
    display_->fill_circle(32, 32, 20, COLOR_ON);

    if (!blink_) {
      // pupil
      display_->fill_circle(pupil_x_, pupil_y_, pupil_radius_, COLOR_OFF);
    } else {
      // eyelid overlay
      display_->filled_rectangle(12, 28, 40, 8, COLOR_OFF);
    }
  }

  // exposed controls
  void blink_once() { blink_ = true; }
  void open_eye() { blink_ = false; }
  void move_pupil(int x, int y) { pupil_x_ = x; pupil_y_ = y; }
  void set_pupil_radius(int r) { pupil_radius_ = r; }

 private:
  display::DisplayBuffer *display_;
  bool blink_;
  int pupil_x_, pupil_y_, pupil_radius_;
  int blink_timer_;
};

}  // namespace roboeyes
}  // namespace esphome
