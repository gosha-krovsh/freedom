#include "actions_controller.h"

ActionsController::ActionsController(std::shared_ptr<Model> model) :
    model_(std::move(model)) {};

void ActionsController::Call(const std::vector<Action>& command) {
  for (const auto& method_to_call : command) {
    switch (static_cast<Action::ActionType>(method_to_call.GetId())) {
      case Action::ActionType::kMove: {
        Move(method_to_call.GetParametres().at(0),
             Point(std::stoi(method_to_call.GetParametres().at(1)),
                   std::stoi(method_to_call.GetParametres().at(2)),
                   std::stoi(method_to_call.GetParametres().at(3))));
        break;
      }
      case Action::ActionType::kWrongArg: {
        qDebug() << "Wrong Action";
        break;
      }
    }
  }
}

void ActionsController::Tick() {
  if (model_->GetSchedule().IsNextActionAvailable(model_->GetTime())) {
    Call(model_->GetSchedule().GetActionByTime(model_->GetTime()));
  }
}

// All Implementation-defined methods
void ActionsController::Move(const std::string& bot_name, const Point& place) {
  if (bot_name == "Hero") {
    model_->GetHero().SetCoordinates(place);
  }
}
// ----------------------------------
