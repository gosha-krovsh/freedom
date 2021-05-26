#include "controller.h"

Controller::Controller()
    : model_(std::make_shared<Model>()),
      view_(std::make_unique<View>(this, model_)),
      actions_controller_(std::make_unique<ActionController>(this, model_)),
      data_controller_(std::make_unique<DataController>(model_)),
      quest_controller_(std::make_unique<QuestController>(this, model_)),
      item_controller_(std::make_unique<ItemController>(model_)),
      current_tick_(0) {
  model_->SetMap(std::move(data_controller_->ParseGameMap()));
  model_->SetSchedule(std::move(data_controller_->ParseSchedule()));
  model_->SetBots(std::move(data_controller_->ParseBots()));
  model_->SetConversations(std::move(data_controller_->ParseConversations()));
  model_->SetQuests(std::move(data_controller_->ParseQuests()));
  model_->SetCreatureStorage(
      std::move(data_controller_->ParseCreatureStorage()));

  view_->AssignHeroStorage();
  view_->Show();
}

void Controller::Tick() {
  data_controller_->Tick(current_tick_);
  quest_controller_->Tick(current_tick_);
  model_->GetHero().Tick(current_tick_);
  model_->GetSound().Tick(current_tick_);

  for (auto& bot : model_->GetBots()) {
    bot->Tick(current_tick_);
    TryToOpenDoor(*bot);
  }
  model_->GetMap().UpdateCurrentRoom(model_->GetHero().GetRoundedX(),
                                     model_->GetHero().GetRoundedY());

  if (current_tick_ % constants::kTicksInMinute == 0 &&
      current_tick_ != 0) {
    model_->GetTime().AddMinutes(1);
    qDebug() << QString::fromStdString(model_->GetTime().ToString());
    actions_controller_->Tick(current_tick_);
  }

  CheckHeroCollision();
  ProcessPoliceSupervision();
  ProcessFighting();

  model_->GetMap().Tick(current_tick_);

  // In order to close inventory, if hero has left without closing it.
  if (view_->IsItemDialogOpen() && (GetInteractableStorage() == nullptr)) {
    view_->ItemDialogEvent();
  }

  view_->UpdateStatusBar();

  ++current_tick_;
}

std::shared_ptr<Storage> Controller::GetInteractableStorage() {
  auto bot = FindNearestDestroyedBot().get();
  auto obj = GetNearestOfTwoObjects(FindNearestStorableObject(), bot);
  if (!view_->IsItemDialogOpen() && (obj != bot)) {
    PlayTrack(Sound::kOpenChest);
  }
  return obj ? obj->GetStorage() : nullptr;
}

Object* Controller::FindNearestStorableObject() {
  return FindIfNearestObject([](Object* block) {
    return block->IsStorable();
  });
}

void Controller::ProcessPoliceSupervision() {
  auto hero_clothes_name = model_->GetHero().GetClothesName();

  bool unauthorized_access_to_danger_zone =
      (model_->GetMap().GetCurrentRoom().danger_zone &&
       hero_clothes_name != constants::kPoliceClothesName);
  bool without_clothes =
      (hero_clothes_name == constants::kEmptyClothesName);

  bool illegal_act = (unauthorized_access_to_danger_zone ||
                      without_clothes);

  if (!illegal_act) {
    return;
  }

  auto hero_coords = model_->GetHero().GetCoordinates();

  for (const auto& bot : model_->GetBots()) {
    if (bot->GetBotType() == Bot::Type::kPolice && !bot->IsDestroyed()) {
      double dist = bot->GetCoordinates().DistanceFrom(hero_coords);
      if (dist < constants::kAttackRadius) {
        model_->CreateFightingPairIfNotExists(&model_->GetHero(), bot.get());
        bot->SetTargets({});
        continue;
      } else if (dist < constants::kPoliceIllegalDetectionRadius) {
        if (bot->GetFinish() == hero_coords) {
          continue;
        }

        // Point for searching wall
        Point p = hero_coords;
        auto step = (-hero_coords + bot->GetCoordinates()).Normalized() *
                     constants::kStepForSearchingWall;

        bool overlapping_field_of_view = false;
        while (dist > constants::kStepForSearchingWall) {
          auto block = model_->GetMap().GetBlock(p);
          if (block && block->IsTouchable()) {
            overlapping_field_of_view = true;
            break;
          }
          p += step;
          dist -= constants::kStepForSearchingWall;
        }

        if (!overlapping_field_of_view) {
          BuildPath(bot, hero_coords.GetRounded());
          continue;
        }
      }
    }
  }
}

void Controller::ProcessFighting() {
  for (const auto& pair : model_->GetFightingPairs()) {
    ProcessFighting(pair.first, pair.second);
  }
  model_->DeleteFinishedFightingPairs();
}

void Controller::ProcessFighting(Creature* attacker, Creature* victim) {
  if (!attacker->IsAbleToAttack() || victim->IsDestroyed()) {
    return;
  }
  PlayTrack(Sound::kFight);
  victim->DecreaseHP(attacker->GetAttack());
  attacker->RefreshAttackCooldown();
  if (!victim->IsDestroyed()) {
    victim->Shake(victim->GetCoordinates() - attacker->GetCoordinates());
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

  auto nearest_bot = FindNearestAliveBotInRadius(constants::kAttackRadius);
  if (nearest_bot) {
    model_->CreateFightingPairIfNotExists(&hero, nearest_bot.get());
    return;
  }

  auto nearest_wall = FindNearestObjectWithType(Object::Type::kWall);
  if (nearest_wall) {
    PlayTrack(Sound::kWallAttack);
    nearest_wall->Interact(hero);
    hero.RefreshAttackCooldown();
  }
}

std::shared_ptr<Bot> Controller::FindIfNearestBotInRadius(double radius,
      const std::function<bool(const std::shared_ptr<Bot>&)>& predicate) {
  Hero& hero = model_->GetHero();
  Point hero_coords = hero.GetCoordinates() +
      constants::kCoefficientForShiftingCircleAttack * radius *
          hero.GetViewVector();
  double squared_radius = radius * radius;

  std::shared_ptr<Bot> nearest_bot = nullptr;
  double squared_distance = squared_radius;
  for (auto& bot : model_->GetBots()) {
    double new_squared_distance =
        hero_coords.SquaredDistanceFrom(bot->GetCoordinates());
    if (new_squared_distance < squared_distance && predicate(bot)) {
      squared_distance = new_squared_distance;
      nearest_bot = bot;
    }
  }
  return nearest_bot;
}

std::shared_ptr<Bot> Controller::FindNearestDestroyedBot() {
  return FindIfNearestBotInRadius(1 + constants::kDistanceToDetectBlock,
                                  [](const std::shared_ptr<Bot>& bot) {
    return bot->IsDestroyed();
  });
}

Object* Controller::FindNearestObjectWithType(Object::Type type) {
  return FindIfNearestObject([type](Object* object) {
    return object->IsType(type);
  });
}

void Controller::BuildPath(const std::shared_ptr<Bot>& bot,
                           const Point& finish) {
  Point start = bot->GetCoordinates();

  std::unordered_map<Point, Point, Point::HashFunc> prev;
  std::deque<Point> current;
  std::unordered_map<Point, bool, Point::HashFunc> used;

  prev[start] = Point(-1, -1, -1);
  used[start] = true;

  current.push_front(start);
  while (!current.empty() && !used[finish]) {
    Point current_point = current.front();
    current.pop_front();
    for (int delta_x = -1; delta_x <= 1; ++delta_x) {
      for (int delta_y = -1; delta_y <= 1; ++delta_y) {
        int new_x = current_point.x + delta_x;
        int new_y = current_point.y + delta_y;
        Point next_point = Point(new_x, new_y, 1);

        auto next_block = model_->GetMap().GetBlock(next_point);

        bool is_openable_door_ = false;
        if (next_block != nullptr &&
            (next_block->IsType(Object::Type::kDoor_315) ||
                next_block->IsType(Object::Type::kDoor_225))) {
          Door* next_door = static_cast<Door*>(next_block);
          is_openable_door_ = next_door->IsOpenable();
        }

        if (!used[next_point] &&
            (next_block == nullptr || is_openable_door_)) {
          used[next_point] = true;
          prev[next_point] = current_point;
          if (delta_x == 0 || delta_y == 0) {
            current.push_front(next_point);
          } else {
            current.push_back(next_point);
          }
        }
      }
    }
  }

  bot->SetTargets(CollectPath(finish, prev));
}

std::vector<Point> Controller::CollectPath(const Point& finish,
                                           const std::unordered_map
                                           <Point, Point, Point::HashFunc>&
                                           prev) const {
  Point current_point = finish;

  std::vector<Point> result;
  while (current_point != Point(-1, -1, -1)) {
    result.push_back(current_point);
    current_point = prev.at(current_point);
  }

  std::reverse(result.begin(), result.end());
  return result;
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
        double distance_squared = hero_coords.SquaredDistanceFrom({x, y, 1});
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
  if (model_->GetHero().IsDestroyed()) {
    return;
  }
  model_->GetHero().UpdateMovement(control_key_states_.left,
                                   control_key_states_.up,
                                   control_key_states_.right,
                                   control_key_states_.down);
}

void Controller::OnItemPress(int bar_id, int index) {
  std::pair<ItemBar*, ItemBar*> source_dest = view_->GetSrcDestBars(bar_id,
                                                                    index);
  if (source_dest.first != nullptr && source_dest.second != nullptr &&
     (source_dest.second->GetStorage()->HasLessItems(
         source_dest.second->GetMaxItemCount()))) {
    MoveItem(index, source_dest.first->GetStorage(),
             source_dest.second->GetStorage());
    source_dest.first->UpdateIcons();
    source_dest.second->UpdateIcons();
    PlayTrack(Sound::kTakeItem);
  }
}

void Controller::UseItem(const Item& item) {
  item_controller_->UseItem(item);
}

void Controller::MoveItem(int index,
                          const std::shared_ptr<Storage>& source,
                          const std::shared_ptr<Storage>& destination) {
  if (source->IsValidIndex(index)) {
    destination->PutItem(source->RemoveItem(index));
  }
}

void Controller::OpenEyes() {
  view_->ShowGame();
}
void Controller::CloseEyes() {
  view_->HideGame();
  model_->GetSound().PlayTrack(Sound::kIntro);
}
void Controller::StartConversation(const Creature* creature) {
  view_->StartConversation(creature->GetCurrentConversation());
}

std::shared_ptr<Conversation> Controller::GetNearestConversation() {
  auto bot = FindNearestAliveBotInRadius(constants::kStartConversationRadius);
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

void Controller::MoveAllBotsToPoint(const Point& point) {
  auto cmp = [](std::pair<double, Point> lhs, std::pair<double, Point> rhs) {
    return lhs.first < rhs.first;
  };
  std::set<std::pair<double, Point>, decltype(cmp)> targets_near_point(cmp);

  for (int x = 0; x < model_->GetMap().GetXSize(); ++x) {
    for (int y = 0; y < model_->GetMap().GetYSize(); ++y) {
      if (model_->GetMap().GetBlock(x, y, 1) == nullptr) {
        targets_near_point.insert({point.DistanceFrom({x, y, 1}), {x, y, 1}});
      }
    }
  }

  auto current_point_iter = targets_near_point.begin();
  for (auto& bot : model_->GetBots()) {
    BuildPath(bot, current_point_iter->second);
    ++current_point_iter;
  }
}

void Controller::ExecuteActions(const std::vector<Action>& actions) {
  actions_controller_->Call(actions);
}

void Controller::StartQuest(int id) {
  quest_controller_->StartQuest(id);
}

void Controller::InteractWithDoor() {
  Door* door = static_cast<Door*>(GetNearestOfTwoObjects(
      FindNearestObjectWithType(Object::Type::kDoor_225),
      FindNearestObjectWithType(Object::Type::kDoor_315)));
  if (door) {
    bool state_before = door->IsOpened();
    door->Interact(model_->GetHero());
    bool state_after = door->IsOpened();
    if (state_before != state_after) {
      PlayTrack(Sound::kOpenDoor);
    }
  }
}

Object* Controller::GetNearestOfTwoObjects(Object* obj1, Object* obj2) const {
  if (obj1 && obj2) {
    Point hero_coords = model_->GetHero().GetCoordinates();
    return (hero_coords.DistanceFrom(obj1->GetCoordinates()) <=
            hero_coords.DistanceFrom(obj2->GetCoordinates())) ? obj1 : obj2;
  }
  return obj1 ? obj1 : obj2;
}

std::shared_ptr<Bot> Controller::FindNearestAliveBotInRadius(double radius) {
  return FindIfNearestBotInRadius(radius, [](const std::shared_ptr<Bot>& bot) {
    return (!bot->IsDestroyed());
  });
}

void Controller::CloseMainMenu() {
  view_->CloseMainMenu();
}

void Controller::UpdateSound() {
  model_->GetSound().UpdateSettings();
}


void Controller::DeleteQuestFromList(const QString& quest_name) {
  view_->GetQuestTaskList()->DeleteQuest(quest_name);
}

void Controller::AddQuestToList(const QString& quest_name,
                                const std::vector<QString>& node_strings) {
  view_->AddQuestToTaskList(quest_name, node_strings);
}

void Controller::UpdateQuestList(const QString& quest_name, int index) {
  view_->UpdateQuestTaskList(quest_name, index);
}

void Controller::TryToOpenDoor(const Bot& bot) {
  for (int delta_x = -1; delta_x <= 1; ++delta_x) {
    for (int delta_y = -1; delta_y <= 1; ++delta_y) {
      auto block =
          model_->GetMap().GetBlock(bot.GetX() + delta_x,
                                    bot.GetY() + delta_y, 1);

      Door* door = nullptr;
      if (block != nullptr && (block->IsType(Object::Type::kDoor_225) ||
          block->IsType(Object::Type::kDoor_315))) {
        door = static_cast<Door*>(block);
      }
      if (door != nullptr && !door->IsOpened()) {
        door->Interact(bot);
      }
    }
  }
}

void Controller::PlayTrack(Sound::SoundAction action, int volume) {
  model_->GetSound().PlayTrack(action, volume);
}

void Controller::PlayTrackOnce(Sound::SoundAction action, int volume) {
  model_->GetSound().PlayTrackOnce(action, volume);
}
