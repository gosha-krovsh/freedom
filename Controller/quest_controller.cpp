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
    const std::shared_ptr<AbstractQuestNode>& quest_node) {
  switch (quest_node->GetQuestNodeType()) {
    case AbstractQuestNode::QuestNodeType::kMoveToDestination: {
      return CheckCondition(
          std::static_pointer_cast<MoveToDestinationQuestNode>(quest_node));
    }
    default: {
      qDebug() << "Unhandled QuestNodeType";
      return false;
    }
  }
}

bool QuestController::CheckCondition(
    const std::shared_ptr<MoveToDestinationQuestNode>& quest_node) {
  auto hero = model_->GetHero();
  auto destination = quest_node->GetDestination();
  return AreRoundedEqual(hero.GetCoordinates(), destination);
}
