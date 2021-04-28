#include "action_controller.h"

ActionController::ActionController(const std::shared_ptr<Model>& model) :
    model_(model) {}

void ActionController::Call(const std::vector<Action>& command) {
  for (const auto& method_to_call : command) {
    switch (method_to_call.GetActionType()) {
      case Action::ActionType::kMove: {
        Move(std::stoi(method_to_call.GetParameters().at(0)),
             Point(std::stoi(method_to_call.GetParameters().at(1)),
                   std::stoi(method_to_call.GetParameters().at(2)),
                   std::stoi(method_to_call.GetParameters().at(3))));
        break;
      }
      case Action::ActionType::kWrongArg: {
        qDebug() << "Wrong Action";
        break;
      }
    }
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
