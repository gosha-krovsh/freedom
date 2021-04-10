#include "controller.h"

Controller::Controller()
    : model_(std::make_shared<Model>(DataController::ParseSchedule(),
                                     DataController::ParseGameMap())),
      view_(std::make_unique<View>(this, model_)),
      actions_controller_(std::make_unique<ActionController>(model_)),
      data_controller_(std::make_unique<DataController>(model_)),
      current_tick_(0) {}

void Controller::Tick() {
  data_controller_->Tick(current_tick_);
  model_->GetHero().Tick(current_tick_);
  model_->GetMap().UpdateCurrentRoom(model_->GetHero().GetRoundedX(),
                                     model_->GetHero().GetRoundedY());

  if (current_tick_ % constants::kTicksInMinute == 0 && current_tick_ != 0) {
    model_->GetTime().AddMinutes(1);
    actions_controller_->Tick(current_tick_);
  }
  CheckHeroCollision();

  ++current_tick_;
}

void Controller::CheckHeroCollision() {
  Hero& hero = model_->GetHero();

  int floored_x = hero.GetFlooredX();
  int floored_y = hero.GetFlooredY();

  // Check 4 blocks, which |Hero| can collide
  for (int block_x = floored_x; block_x <= floored_x + 1; ++block_x) {
    for (int block_y = floored_y; block_y <= floored_y + 1; ++block_y) {
      auto block = model_->GetMap().GetBlock(block_x, block_y,
                                             hero.GetRoundedZ());
      if (block == nullptr || !block->IsTouchable()) {
        continue;
      }

      double delta_x = hero.GetX() - block_x;
      double delta_y = hero.GetY() - block_y;
      if (std::abs(delta_x) + std::abs(delta_y) < constants::kMaxSumOfDeltas) {
        if (delta_x > 1. - constants::kOffsetForCollisionDetection) {
          hero.SetX(block_x + 1);
        } else if (delta_x < -(1. - constants::kOffsetForCollisionDetection)) {
          hero.SetX(block_x - 1);
        } else if (delta_y > 1. - constants::kOffsetForCollisionDetection) {
          hero.SetY(block_y + 1);
        } else if (delta_y < -(1. - constants::kOffsetForCollisionDetection)) {
          hero.SetY(block_y - 1);
        }
      }
    }
  }
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
  model_->GetHero().UpdateMovement(control_key_states_.left,
                                   control_key_states_.up,
                                   control_key_states_.right,
                                   control_key_states_.down);
}
