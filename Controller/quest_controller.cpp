#include "quest_controller.h"

QuestController::QuestController(const std::shared_ptr<Model>& model) :
    model_(model) {}

void QuestController::StartQuest(int id) {
  model_->SetCurrentQuestById(id);
  // TODO: handle current_quest_->OnStart();
}

void QuestController::Tick(int) {
  auto current_quest = model_->GetCurrentQuest();
  if (!current_quest) {
    return;
  }

  auto current_quest_node = current_quest->GetCurrentQuestNode();
  if (current_quest_node) {
    if (CheckCondition(current_quest_node)) {
      current_quest->MoveToNextQuestNode();
    }
  } else {
    // TODO: handle current_quest_->OnFinish();
    model_->ResetCurrentQuest();
    qDebug() << "Quest finished";  // message to test
  }
}

bool QuestController::CheckCondition(
    const std::shared_ptr<QuestNode>& quest_node) {
  auto params = quest_node->GetParams();
  switch (quest_node->GetType()) {
    case QuestNode::Type::kMoveToDestination: {
      Point destination = {params[0].toDouble(),
                           params[1].toDouble(),
                           params[2].toDouble()};
      return CheckMoveToDestinationCondition(destination);
    }
    default: {
      qDebug() << "Unhandled Type";
      return false;
    }
  }
}

bool QuestController::CheckMoveToDestinationCondition(
    const Point& destination) {
  auto hero = model_->GetHero();
  return AreRoundedEqual(hero.GetCoordinates(), destination);
}
