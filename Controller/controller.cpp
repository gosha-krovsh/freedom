#include "controller.h"

Controller::Controller() : view_(std::make_unique<View>(this)),
                           model_(std::make_unique<Model>()) {}

using Map = std::vector<std::vector<std::vector<Object*>>>;
const Map& Controller::GetMap() const {
  return model_->GetMap();
}
const Hero& Controller::GetHero() const {
  return model_->GetHero();
}
Hero& Controller::GetHero() {
  return model_->GetHero();
}

void Controller::UpKeyPressed() {
  button_states_.up = true;
  ProcessPressedButtons();
}
void Controller::RightKeyPressed() {
  button_states_.right = true;
  ProcessPressedButtons();
}
void Controller::DownKeyPressed() {
  button_states_.down = true;
  ProcessPressedButtons();
}
void Controller::LeftKeyPressed() {
  button_states_.left = true;
  ProcessPressedButtons();
}

void Controller::UpKeyRelease() {
  button_states_.up = false;
  ProcessPressedButtons();
}
void Controller::RightKeyRelease() {
  button_states_.right = false;
  ProcessPressedButtons();
}
void Controller::DownKeyRelease() {
  button_states_.down = false;
  ProcessPressedButtons();
}
void Controller::LeftKeyRelease() {
  button_states_.left = false;
  ProcessPressedButtons();
}

void Controller::ProcessPressedButtons() {
  Hero& hero = model_->GetHero();

  bool up = button_states_.up;
  bool right = button_states_.right;
  bool down = button_states_.down;
  bool left = button_states_.left;

  hero.SetMoving(true);
  if (up && !down) {
    if (right && !left) {
      hero.SetViewDirection(kUpRight);
    } else if (left && !right) {
      hero.SetViewDirection(kUpLeft);
    } else {
      hero.SetViewDirection(kUp);
    }
  } else if (down && !up) {
    if (right && !left) {
      hero.SetViewDirection(kDownRight);
    } else if (left && !right) {
      hero.SetViewDirection(kDownLeft);
    } else {
      hero.SetViewDirection(kDown);
    }
  } else {
    if (right && !left) {
      hero.SetViewDirection(kRight);
    } else if (left && !right) {
      hero.SetViewDirection(kLeft);
    } else {
      hero.SetMoving(false);
    }
  }
}
