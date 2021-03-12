#include "controller.h"

Controller::Controller() : model_(std::make_shared<Model>()),
                           view_(std::make_unique<View>(this, model_)) {}

void Controller::Tick() {
  model_->GetHero().Move();
}

void Controller::SetControlUpKeyState(bool state) {
  control_key_states_.up = state;
  UpdateMovingDirection();
}
void Controller::SetControlRightKeyState(bool state) {
  control_key_states_.right = state;
  UpdateMovingDirection();
}
void Controller::SetControlDownKeyState(bool state) {
  control_key_states_.down = state;
  UpdateMovingDirection();
}
void Controller::SetControlLeftKeyState(bool state) {
  control_key_states_.left = state;
  UpdateMovingDirection();
}

void Controller::UpdateMovingDirection() {
  model_->GetHero().SetMovingDirection(control_key_states_.left,
                                       control_key_states_.up,
                                       control_key_states_.right,
                                       control_key_states_.down);
}
