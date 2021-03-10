#include "controller.h"

Controller::Controller() : model_(std::make_unique<Model>()),
                           view_(std::make_unique<View>(this,
                                                        model_.get())) {}

void Controller::Tick() {
  model_->GetHero().Move();
}

void Controller::SetControlUpKeyState(bool state) {
  movement_condition.up = state;
  model_->GetHero().SetMovingDirection(movement_condition);
}
void Controller::SetControlRightKeyState(bool state) {
  movement_condition.right = state;
  model_->GetHero().SetMovingDirection(movement_condition);
}
void Controller::SetControlDownKeyState(bool state) {
  movement_condition.down = state;
  model_->GetHero().SetMovingDirection(movement_condition);
}
void Controller::SetControlLeftKeyState(bool state) {
  movement_condition.left = state;
  model_->GetHero().SetMovingDirection(movement_condition);
}
