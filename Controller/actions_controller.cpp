#include "actions_controller.h"
#include <QDebug>
#include <utility>

ActionsController::ActionsController(std::shared_ptr<Model> model) {
  model_ = std::move(model);
}

void ActionsController::Call(std::vector<EncryptedMethod> command) {
  for (const auto& method_to_call : command) {
    switch (static_cast<EncryptedMethod::MethodId>(method_to_call.id)) {
      case EncryptedMethod::MethodId::kMove: {
        Move(method_to_call.parameters.at(0),
             Point(
                 std::stoi(method_to_call.parameters.at(1)),
                 std::stoi(method_to_call.parameters.at(2)),
                 std::stoi(method_to_call.parameters.at(3))));
        break;
      }
      default: {
        qDebug() << "Wrong Action";
      }
    }
  }
}

void ActionsController::Tick() {
  if (model_->GetShedule().IsNextActionAvailable(model_->GetTime())) {
    Call(model_->GetShedule().GetNextAction(model_->GetTime()));
  }
}

// All Implementation-defined methods
void ActionsController::Move(const std::string& bot_name, const Point& place) {
  if (bot_name == "Hero") {
    model_->GetHero().SetCoordinates(place);
  }
}
// ----------------------------------
