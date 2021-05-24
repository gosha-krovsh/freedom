#include "action_controller.h"

ActionController::ActionController(AbstractController* controller,
                                   const std::shared_ptr<Model>& model) :
                                   controller_(controller),
                                   model_(model) {}

void ActionController::Call(const Action& method) {
  switch (method.GetActionType()) {
    case Action::ActionType::kMove: {
      Move(method.GetParameters().at(0).toInt(),
           Point(method.GetParameters().at(1).toInt(),
                 method.GetParameters().at(2).toInt(),
                 method.GetParameters().at(3).toInt()));
      break;
    }
    case Action::ActionType::kAddItemToStorage: {
      AddItemToStorage(Point(method.GetParameters().at(0).toInt(),
                             method.GetParameters().at(1).toInt(),
                             method.GetParameters().at(2).toInt()),
                       static_cast<Item::Type>(
                           method.GetParameters().at(3).toInt()));
      break;
    }
    case Action::ActionType::kAddItemToBot: {
      AddItemToBot(method.GetParameters().at(0),
                   static_cast<Item::Type>(
                       method.GetParameters().at(1).toInt()));
      break;
    }
    case Action::ActionType::kStartQuest: {
      StartQuest(method.GetParameters().at(0).toInt());
      break;
    }
    case Action::ActionType::kStartFight: {
      StartFight(method.GetParameters().at(0));
      break;
    }
    case Action::ActionType::kLockDoor: {
      LockDoor(Point(method.GetParameters().at(0).toInt(),
                     method.GetParameters().at(1).toInt(),
                     method.GetParameters().at(2).toInt()));
      break;
    }
    case Action::ActionType::kUnlockDoor: {
      UnlockDoor(Point(method.GetParameters().at(0).toInt(),
                       method.GetParameters().at(1).toInt(),
                       method.GetParameters().at(2).toInt()));
      break;
    }
    case Action::ActionType::kSetBotConversation: {
      SetBotConversation(method.GetParameters().at(0),
                         method.GetParameters().at(1).toInt());
      break;
    }
    case Action::ActionType::kWrongArg: {
      qDebug() << "Wrong Action";
      break;
    }
  }
}

void ActionController::Call(const std::vector<Action>& methods) {
  for (const auto& method : methods) {
    Call(method);
  }
}

void ActionController::Tick(int) {
  if (model_->GetSchedule().IsNextActionAvailable(model_->GetTime())) {
    Call(model_->GetSchedule().GetActionByTime(model_->GetTime()));
  }
}

void ActionController::Move(int id, const Point& place) {
  if (id == -1) {
    model_->GetHero().SetCoordinates(place);
  }
  // todo: bots
}

void ActionController::AddItemToBot(const QString& bot_name,
                                    Item::Type item_type) {
  auto name = Item::GetNameByType(item_type);
  model_->GetBotByName(bot_name)->GetStorage()->PutItem(
      Item(item_type,
           name,
           model_->GetImage(name.toLower())));
}
void ActionController::AddItemToStorage(const Point& coords,
                                        Item::Type item_type) {
  auto chest = dynamic_cast<Chest*>(model_->GetMap().GetBlock(coords));

  if (chest) {
    auto name = Item::GetNameByType(item_type);
    chest->GetStorage()->PutItem(Item(item_type,
                                      name,
                                      model_->GetImage(name.toLower())));
  }
}

void ActionController::StartQuest(int id) {
  controller_->StartQuest(id);
}

void ActionController::StartFight(const QString& name) {
  model_->CreateFightingPair(&model_->GetHero(),
                             model_->GetBotByName(name).get());
}

void ActionController::LockDoor(const Point& coords) {
  auto door = dynamic_cast<Door*>(model_->GetMap().GetBlock(coords));

  if (door) {
    door->Lock();
  }
}
void ActionController::UnlockDoor(const Point& coords) {
  auto door = dynamic_cast<Door*>(model_->GetMap().GetBlock(coords));

  if (door) {
    door->Unlock();
  }
}

void ActionController::SetBotConversation(const QString& bot_name,
                                          int conversation_id) {
  model_->GetBotByName(bot_name)->SetCurrentConversation(
      model_->GetConversationById(conversation_id));
}
