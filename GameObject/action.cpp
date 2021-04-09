#include "action.h"

Action::Action(const std::string& name,
               const std::vector<std::string>& parametres) :
    action_type_(ChooseActionType(name)),
    parametres_(parametres) {}

Action::ActionType Action::GetActionType() const {
  return action_type_;
}

std::vector<std::string> Action::GetParametres() const {
  return parametres_;
}

Action::ActionType Action::ChooseActionType(const std::string& name) {
  if (Equals(name, "move")) {
    return kMove;
  }

  return kWrongArg;
}

bool Action::Equals(const std::string& lhs, const std::string& rhs) {
  return std::equal(lhs.begin(), lhs.end(),
                    rhs.begin(), rhs.end(),
                    [](char a, char b) {
                      return tolower(a) == tolower(b);
                    });
}
