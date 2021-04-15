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

StorableObject* Controller::CheckStorableBlocks() {
  // !DEPRECATED CODE! Will be fixed at merging
  Hero& hero = model_->GetHero();
  int floored_x = std::floor(hero.GetX());
  int floored_y = std::floor(hero.GetY());

  auto map = model_->GetMap();
  for (int x = floored_x - 1; x <= floored_x + 2; ++x) {
    for (int y = floored_y - 1; y <= floored_y + 2; ++y) {
      auto storable_obj =
          dynamic_cast<StorableObject*>(map[hero.GetRoundedZ()][y][x]);

      if (storable_obj) {
        return storable_obj;
      }
    }
  }

  return nullptr;
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

void Controller::OnItemPress(int bar_id, int index) {
  std::pair<ItemBar*, ItemBar*> sourse_dest = view_->GetSrcDestBars(bar_id);
  if (sourse_dest.first && sourse_dest.second) {
    MoveItem(index, sourse_dest.first->GetObject(),
                    sourse_dest.second->GetObject());
    sourse_dest.first->UpdateIcons();
    sourse_dest.second->UpdateIcons();
  }
}

void Controller::MoveItem(int index, StorableObject* sourse,
                          StorableObject* destination) {
  // Moves item from one object to another via index.
  if (sourse->isValidIndex(index)) {
    destination->PutItem(sourse->RemoveItem(index));
  }
}
