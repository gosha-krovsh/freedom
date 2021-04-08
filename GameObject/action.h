#ifndef GAMEOBJECT_ACTION_H_
#define GAMEOBJECT_ACTION_H_

#include <string>
#include <utility>
#include <vector>

class Action {
 public:
  enum ActionType {
    kWrongArg = 0,
    kMove = 1
  };

  Action(const std::string&, std::vector<std::string>);

  ActionType GetActionType() const;
  std::vector<std::string> GetParametres() const;

 private:
  ActionType ChooseActionType(const std::string& name);
  bool Equals(const std::string& lhs, const std::string& rhs);

  ActionType action_type_;
  std::vector<std::string> parametres_;
};

#endif  // GAMEOBJECT_ACTION_H_
