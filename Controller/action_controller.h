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

  // All Implementation-defined methods
 private:
  void Move(const std::string& bot_name, const Point& place);

 private:
  std::shared_ptr<Model> model_;
};

#endif  // CONTROLLER_ACTION_CONTROLLER_H_
