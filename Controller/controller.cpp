#include "controller.h"

Controller::Controller()
    : model_(std::make_shared<Model>(DataController::ParseSchedule())),
      view_(std::make_unique<View>(this, model_)),
      actions_controller_(std::make_unique<ActionController>(model_)),
      data_controller_(std::make_unique<DataController>(model_)),
      current_tick_(0) {}

void Controller::Tick() {
  data_controller_->Tick(current_tick_);
  model_->GetHero().Tick(current_tick_);

  if (current_tick_ % constants::kTicksInMinute == 0 && current_tick_ != 0) {
    model_->GetTime().AddMinutes(1);
    actions_controller_->Tick(current_tick_);
  }
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
        // Check for collision with corner of block
        // when |Hero| moves diagonally
        if (std::abs(delta_x) > 1. - constants::kOffsetForCollisionDetection &&
            std::abs(delta_y) > 1. - constants::kOffsetForCollisionDetection) {
          switch (hero.GetViewDirection()) {
            case DynamicObject::ViewDirection::kUpLeft:
            case DynamicObject::ViewDirection::kDownRight: {
              hero.SetX(block_x + std::round(delta_x));
              break;
            }
            case DynamicObject::ViewDirection::kUpRight:
            case DynamicObject::ViewDirection::kDownLeft: {
              hero.SetY(block_y + std::round(delta_y));
              break;
            }
            default: {
              break;
            }
          }
        }

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
  if (!hero.IsAbleToAttack()) {
    return;
  }

  Point view_vector = hero.GetViewVector() *
                      constants::kDistanceToDetectBlock;
  Point hero_coords = hero.GetCoordinates() + view_vector;

  double min_distance_squared = (1 + constants::kDistanceToDetectBlock) *
                                (1 + constants::kDistanceToDetectBlock);
  Wall* nearest_wall = nullptr;

  int floored_x = std::floor(hero.GetX());
  int floored_y = std::floor(hero.GetY());
  auto map = model_->GetMap();
  for (int x = floored_x - 1; x <= floored_x + 2; ++x) {
    for (int y = floored_y - 1; y <= floored_y + 2; ++y) {
      auto wall = dynamic_cast<Wall*>(map[hero.GetRoundedZ()][y][x]);

      if (wall && !wall->IsDestroyed()) {
        double distance_squared = (hero_coords.x - x) * (hero_coords.x - x) +
                                  (hero_coords.y - y) * (hero_coords.y - y);
        if (distance_squared < min_distance_squared + constants::kEps) {
          min_distance_squared = distance_squared;
          nearest_wall = wall;
        }
      }
    }
  }

  if (nearest_wall) {
    nearest_wall->DecreaseHP(constants::kAttack);

    Point direction_of_shake{nearest_wall->GetRoundedX() - hero.GetRoundedX(),
                             nearest_wall->GetRoundedY() - hero.GetRoundedY()};
    nearest_wall->Shake(direction_of_shake);

    hero.RefreshAttackCooldown();
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
