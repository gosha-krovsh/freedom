#include "controller.h"

Controller::Controller() : model_(std::make_shared<Model>()),
                           view_(std::make_unique<View>(this, model_)),
                           current_tick_(0) {}

void Controller::Tick() {
  model_->GetHero().Tick(current_tick_);
  CheckHeroCollision();

  for (auto& object : model_->GetObjects()) {
    object->Tick(current_tick_);
  }

  ++current_tick_;
}

void Controller::CheckHeroCollision() {
  Hero& hero = model_->GetHero();

  int floored_x = std::floor(hero.GetX());
  int floored_y = std::floor(hero.GetY());

  // Check 4 blocks, which |Hero| can collide
  for (int block_x = floored_x; block_x <= floored_x + 1; ++block_x) {
    for (int block_y = floored_y; block_y <= floored_y + 1; ++block_y) {
      const Object* block = model_->GetMap()[hero.GetRoundedZ()]
                                            [block_y]
                                            [block_x];
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

void Controller::HeroAttack() {
  Hero& hero = model_->GetHero();

  Point view_vector = hero.GetViewVector() *
                      constants::kDistanceToDetectBlock;
  double new_hero_x = hero.GetX() + view_vector.x;
  double new_hero_y = hero.GetY() + view_vector.y;

  double min_distance_in_square = (1 + constants::kDistanceToDetectBlock) *
                                  (1 + constants::kDistanceToDetectBlock);
  Destroyable* nearest_block{};

  int floored_x = std::floor(hero.GetX());
  int floored_y = std::floor(hero.GetY());
  auto map = model_->GetMap();
  for (int x = floored_x - 1; x <= floored_x + 2; ++x) {
    for (int y = floored_y - 1; y <= floored_y + 2; ++y) {
      auto block = dynamic_cast<Destroyable*>(map[hero.GetRoundedZ()][y][x]);

      if (block && !block->IsDestroyed()) {
        double distance_in_square = (new_hero_x - x) * (new_hero_x - x) +
                                    (new_hero_y - y) * (new_hero_y - y);
        if (distance_in_square < min_distance_in_square + constants::kEps) {
          min_distance_in_square = distance_in_square;
          nearest_block = block;
        }
      }
    }
  }

  if (nearest_block) {
    nearest_block->DecreaseHP(constants::kAttack);

    auto* wall = dynamic_cast<Wall*>(nearest_block);
    if (wall) {
      Point direction_of_shake{wall->GetRoundedX() - hero.GetRoundedX(),
                               wall->GetRoundedY() - hero.GetRoundedY()};
      wall->Shake(direction_of_shake);
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
