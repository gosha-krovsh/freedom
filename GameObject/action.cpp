#include "action.h"

Action::Action(const QString& name,
               const std::vector<QString>& parameters) :
    action_type_(ChooseActionType(name)),
    parameters_(parameters) {}

Action::ActionType Action::GetActionType() const {
  return action_type_;
}

std::vector<QString> Action::GetParameters() const {
  return parameters_;
}

Action::ActionType Action::ChooseActionType(const QString& name) {
  if (name == "Move") {
    return kMove;
  } else if (name == "AddItemToStorage") {
      return kAddItemToStorage;
  } else if (name == "AddItemToBot") {
    return kAddItemToBot;
  } else if (name == "StartQuest") {
    return kStartQuest;
  } else if (name == "SetBotConversation") {
    return kSetBotConversation;
  } else if (name == "LockDoor") {
    return kLockDoor;
  } else if (name == "UnlockDoor") {
    return kUnlockDoor;
  } else if (name == "StartFight") {
    return kStartFight;
  }
  qDebug() << "Invalid action name";
  return kWrongArg;
}
