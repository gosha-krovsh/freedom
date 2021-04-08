#include "action_controller.h"

ActionController::ActionController(std::shared_ptr<Model> model) :
    model_(std::move(model)) {}

void ActionController::Call(const std::vector<Action>& command) {
  for (const auto& method_to_call : command) {
    switch (static_cast<Action::ActionType>(method_to_call.GetId())) {
      case Action::ActionType::kMove: {
        Move(method_to_call.GetParametres().at(0),
             std::stoi(method_to_call.GetParametres().at(1)),
             Point(std::stoi(method_to_call.GetParametres().at(2)),
                   std::stoi(method_to_call.GetParametres().at(3)),
                   std::stoi(method_to_call.GetParametres().at(4))));
        break;
      }
      case Action::ActionType::kWrongArg: {
        qDebug() << "Wrong Action";
        break;
      }
    }
  }
}

void ActionController::Tick() {
  if (model_->GetSchedule().IsNextActionAvailable(model_->GetTime())) {
    Call(model_->GetSchedule().GetActionByTime(model_->GetTime()));
  }
}

void ActionController::Move(const std::string& creature,
                            int id, const Point& place) {
  if (creature == "Hero") {
    model_->GetHero().SetCoordinates(place);
  }
  // todo: bots
}
