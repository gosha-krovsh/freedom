#include "controller.h"

Controller::Controller() : model_(std::make_unique<Model>()),
                           view_(std::make_unique<View>(this,
                                                        model_.get())) {}

void Controller::Tick() {
  model_->GetHero().Move();
}

void Controller::SetControlUpKeyState(bool state) {
  key_states.up = state;
  ProcessControlKeyStates();
}
void Controller::SetControlRightKeyState(bool state) {
  key_states.right = state;
  ProcessControlKeyStates();
}
void Controller::SetControlDownKeyState(bool state) {
  key_states.down = state;
  ProcessControlKeyStates();
}
void Controller::SetControlLeftKeyState(bool state) {
  key_states.left = state;
  ProcessControlKeyStates();
}

void Controller::ProcessControlKeyStates() {
  Hero& hero = model_->GetHero();

  bool up = key_states.up;
  bool right = key_states.right;
  bool down = key_states.down;
  bool left = key_states.left;

  hero.SetMoving(true);
  if (up && !down) {
    if (right && !left) {
      hero.SetViewDirection(ViewDirection::kUpRight);
    } else if (left && !right) {
      hero.SetViewDirection(ViewDirection::kUpLeft);
    } else {
      hero.SetViewDirection(ViewDirection::kUp);
    }
  } else if (down && !up) {
    if (right && !left) {
      hero.SetViewDirection(ViewDirection::kDownRight);
    } else if (left && !right) {
      hero.SetViewDirection(ViewDirection::kDownLeft);
    } else {
      hero.SetViewDirection(ViewDirection::kDown);
    }
  } else {
    if (right && !left) {
      hero.SetViewDirection(ViewDirection::kRight);
    } else if (left && !right) {
      hero.SetViewDirection(ViewDirection::kLeft);
    } else {
      hero.SetMoving(false);
    }
  }
}
