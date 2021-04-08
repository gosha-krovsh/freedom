#ifndef CONTROLLER_ACTION_CONTROLLER_H_
#define CONTROLLER_ACTION_CONTROLLER_H_

#include <QDebug>

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "abstract_controller.h"
#include "Model/model.h"
#include "GameObject/point.h"

class ActionController {
 public:
  explicit ActionController(std::shared_ptr<Model> model);
  void Call(const std::vector<Action>& command);
  void Tick();

  // Methods for actions
 private:
  void Move(const std::string& creature, int id, const Point& place);

 private:
  std::shared_ptr<Model> model_;
};

#endif  // CONTROLLER_ACTION_CONTROLLER_H_
