#ifndef ACTIONS_CONTROLLER_H_
#define ACTIONS_CONTROLLER_H_

#include <memory>

#include "abstract_controller.h"
#include "Model/model.h"
#include "GameObject/point.h"

class ActionsController {
 public:
  explicit ActionsController(std::shared_ptr<Model> model);
  void Call(std::vector<EncryptedMethod> command);
  void Tick();

 private:
  std::shared_ptr<Model> model_;

  // All Implementation-defined methods
 private:
  void Move(const std::string& bot_name, const Point& place);
};

#endif  // ACTIONS_CONTROLLER_H_
