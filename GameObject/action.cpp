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
  }
  return kWrongArg;
}
