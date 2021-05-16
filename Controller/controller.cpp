#include "controller.h"

Controller::Controller()
    : model_(std::make_shared<Model>()),
      view_(std::make_unique<View>(this, model_)),
      actions_controller_(std::make_unique<ActionController>(this, model_)),
      data_controller_(std::make_unique<DataController>(model_)),
      quest_controller_(std::make_unique<QuestController>(this, model_)),
      current_tick_(0) {
  model_->SetMap(std::move(data_controller_->ParseGameMap()));
  model_->SetSchedule(std::move(data_controller_->ParseSchedule()));
  model_->SetConversations(std::move(data_controller_->ParseConversations()));
  model_->SetQuests(std::move(data_controller_->ParseQuests()));
}

void Controller::Tick() {
  data_controller_->Tick(current_tick_);
  quest_controller_->Tick(current_tick_);
  model_->GetHero().Tick(current_tick_);
  model_->GetSound().Tick(current_tick_);

  for (auto& bot : model_->GetBots()) {
    bot.Tick(current_tick_);
  }
  model_->GetMap().UpdateCurrentRoom(model_->GetHero().GetRoundedX(),
                                     model_->GetHero().GetRoundedY());

  if (current_tick_ % constants::kTicksInMinute == 0 &&
      current_tick_ != 0) {
    model_->GetTime().AddMinutes(1);
    actions_controller_->Tick(current_tick_);
  }

  CheckHeroCollision();
  ProcessFighting();

  model_->GetMap().Tick(current_tick_);

  Object* nearest_storage = FindIfNearestObject([](Object* block) {
    return block->IsStorable();
  });
  if (view_->IsItemDialogOpen() && nearest_storage == nullptr) {
    view_->ItemDialogEvent();
  }

  ++current_tick_;
}

void Controller::ProcessFighting(Creature* attacker, Creature* victim, int* i) {
  if (attacker->IsAbleToAttack() &&
      !victim->IsDestroyed() && !attacker->IsDestroyed()) {
    model_->GetSound().PlayTrack(Sound::kFight, constants::kAttackCooldown);
    victim->DecreaseHP(attacker->GetAttack());
    attacker->RefreshAttackCooldown();

    if (victim->IsDestroyed()) {
      attacker->StopFighting();
      model_->DeleteFightingPairWithIndex(*i);
      --*i;
    } else {
      victim->Shake(victim->GetCoordinates() - attacker->GetCoordinates());
    }
  }
}

void Controller::ProcessFighting() {
  for (int i = 0; i < model_->GetNumberOfFightingPairs(); ++i) {
    auto fighting_pair = model_->GetFightingPairWithIndex(i);
    auto first = fighting_pair.first;
    auto second = fighting_pair.second;
    ProcessFighting(first, second, &i);
    ProcessFighting(second, first, &i);
  }
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

  auto nearest_bot = FindNearestBotInRadius(constants::kAttackRadius);
  if (nearest_bot) {
    model_->CreateFightingPair(&hero, nearest_bot);
    hero.StartFighting();
    nearest_bot->StartFighting();
    return;
  }

  auto nearest_wall = FindNearestObjectWithType(Object::Type::kWall);
  if (nearest_wall) {
    model_->GetSound().PlayTrack(Sound::kWallAttack,
                                 constants::kDurationOfShaking);
    nearest_wall->Interact(hero);
    hero.RefreshAttackCooldown();
  }
}

Bot* Controller::FindNearestBotInRadius(double radius) {
  Hero& hero = model_->GetHero();
  Point hero_coords = hero.GetCoordinates() +
                      constants::kCoefficientForShiftingCircleAttack * radius *
                      hero.GetViewVector();
  double squared_radius = radius * radius;

  Bot* nearest_bot = nullptr;
  double squared_distance = squared_radius;
  for (auto& bot : model_->GetBots()) {
    double new_squared_distance =
        hero_coords.SquaredDistanceFrom(bot.GetCoordinates());
    if (!bot.IsDestroyed() && new_squared_distance < squared_distance) {
      squared_distance = new_squared_distance;
      nearest_bot = &bot;
    }
  }

  return nearest_bot;
}

Object* Controller::FindNearestObjectWithType(Object::Type type) {
  return FindIfNearestObject([type](Object* object) {
    return object->IsType(type);
  });
}

Object* Controller::FindIfNearestObject(
    const std::function<bool(Object*)>& predicate) {
  Hero& hero = model_->GetHero();
  Point view_vector = hero.GetViewVector() *
                      constants::kDistanceToDetectBlock;
  Point hero_coords = hero.GetCoordinates() + view_vector;

  double min_distance_squared = (1 + constants::kDistanceToDetectBlock) *
                                (1 + constants::kDistanceToDetectBlock);
  Object* nearest_block = nullptr;

  int floored_x = std::floor(hero.GetX());
  int floored_y = std::floor(hero.GetY());
  auto& map = model_->GetMap();
  for (int x = floored_x - 1; x <= floored_x + 2; ++x) {
    for (int y = floored_y - 1; y <= floored_y + 2; ++y) {
      auto block = map.GetBlock(x, y, hero.GetRoundedZ());

      if (block && predicate(block)) {
        // TODO: change to new functionality
        double distance_squared = (hero_coords.x - x) * (hero_coords.x - x) +
                                  (hero_coords.y - y) * (hero_coords.y - y);
        if (distance_squared < min_distance_squared + constants::kEps) {
          min_distance_squared = distance_squared;
          nearest_block = block;
        }
      }
    }
  }

  return nearest_block;
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
  std::pair<ItemBar*, ItemBar*> source_dest = view_->GetSrcDestBars(bar_id);
  if (source_dest.first != nullptr && source_dest.second != nullptr) {
    MoveItem(index, source_dest.first->GetStorage(),
             source_dest.second->GetStorage());
    source_dest.first->UpdateIcons();
    source_dest.second->UpdateIcons();
  }
}

void Controller::MoveItem(int index,
                          const std::shared_ptr<Storage>& source,
                          const std::shared_ptr<Storage>& destination) {
  if (source->IsValidIndex(index)) {
    destination->PutItem(source->RemoveItem(index));
  }
}

std::shared_ptr<Conversation> Controller::StartConversation() {
  auto bot = FindNearestBotInRadius(constants::kStartConversationRadius);
  if (!bot) {
    return nullptr;
  }
  return bot->GetCurrentConversation();
}

void Controller::FinishConversation() {
  view_->CloseConversationWindow();
}

void Controller::ExecuteAction(const Action& action) {
  actions_controller_->Call(action);
}

void Controller::ExecuteActions(const std::vector<Action>& actions) {
  actions_controller_->Call(actions);
}

void Controller::StartQuest(int id) {
  quest_controller_->StartQuest(0);
}
