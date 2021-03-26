#include "controller.h"

Controller::Controller() : model_(std::make_shared<Model>()),
                           view_(std::make_unique<View>(this, model_)),
                           current_tick_(0) {}

void Controller::Tick() {
  model_->GetHero().Tick(current_tick_);
  CheckHeroCollision();

  ++current_tick_;
}

void Controller::CheckHeroCollision() {
  Hero& hero = model_->GetHero();

  int rounded_x = std::floor(hero.GetX());
  int rounded_y = std::floor(hero.GetY());

  // Check 4 blocks, which |Hero| can collide
  for (int block_x = rounded_x; block_x <= rounded_x + 1; ++block_x) {
    for (int block_y = rounded_y; block_y <= rounded_y + 1; ++block_y) {
      const Object* block = model_->GetMap()[std::round(hero.GetZ())]
                                            [block_y]
                                            [block_x];
      if (!block || !block->IsTouchable()) {
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
