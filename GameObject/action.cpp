#include "action.h"

Action::Action(std::string name, std::vector<std::string> parametres) :
    name_(std::move(name)),
    id_(SetId(name_)),
    parametres_(std::move(parametres)) {}

std::string Action::GetName() const {
  return name_;
}

int Action::GetId() const {
  return id_;
}

std::vector<std::string> Action::GetParametres() const {
  return parametres_;
}

int Action::SetId(const std::string& name) {
  if (Equals(name, "move")) {
    return 1;
  }

  return 0;
}

bool Action::Equals(const std::string& lhs, const std::string& rhs) {
  return std::equal(lhs.begin(), lhs.end(),
                    rhs.begin(), rhs.end(),
                    [](char a, char b) {
                      return tolower(a) == tolower(b);
                    });
}
