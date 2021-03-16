#include "controller.h"

Controller::Controller() : model_(std::make_shared<Model>()),
                           view_(std::make_unique<View>(this, model_)),
                           current_tick_(0) {}

void Controller::Tick() {
  model_->GetHero().Tick(current_tick_);
  ++current_tick_;
}

void Controller::SetControlUpKeyState(bool state) {
  control_key_states_.up = state;
  UpdateHeroMovingDirection();
}
void Controller::SetControlRightKeyState(bool state) {
  control_key_states_.right = state;
  UpdateHeroMovingDirection();
}
void Controller::SetControlDownKeyState(bool state) {
  control_key_states_.down = state;
  UpdateHeroMovingDirection();
}
void Controller::SetControlLeftKeyState(bool state) {
  control_key_states_.left = state;
  UpdateHeroMovingDirection();
}
void Controller::UpdateHeroMovingDirection() {
  model_->GetHero().SetMovingDirection(control_key_states_.left,
                                       control_key_states_.up,
                                       control_key_states_.right,
                                       control_key_states_.down);
}
