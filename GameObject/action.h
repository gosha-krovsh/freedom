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

  Action(std::string, std::vector<std::string>);

  std::string GetName() const;
  int GetId() const;
  std::vector<std::string> GetParametres() const;

 private:
  int SetId(const std::string& name);
  bool Equals(const std::string& lhs, const std::string& rhs);

  std::string name_;
  int id_;
  std::vector<std::string> parametres_;
};

#endif  // GAMEOBJECT_ACTION_H_
