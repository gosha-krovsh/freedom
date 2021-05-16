#include "quest_controller.h"

QuestController::QuestController(AbstractController* controller,
                                 const std::shared_ptr<Model>& model) :
                                 controller_(controller),
                                 model_(model) {}

void QuestController::StartQuest(int id) {
  auto quest = model_->GetQuestById(id);
  controller_->ExecuteActions(quest.GetStartActions());
  model_->GetCurrentQuests().emplace_back(quest);
}

void QuestController::FinishQuest(int id) {
  auto& current_quests = model_->GetCurrentQuests();
  auto it = std::find_if(current_quests.begin(), current_quests.end(),
                         [id](const Quest& quest) {
                           return (quest.GetId() == id);
                         });
  if (it == current_quests.end()) {
    qDebug() << "Invalid quest id";
    return;
  }

  controller_->ExecuteActions(it->GetFinishActions());
  current_quests.erase(it);
  qDebug() << "Quest finished";  // message to test
}

void QuestController::Tick(int) {
  auto& current_quests = model_->GetCurrentQuests();
  for (int i = 0; i < current_quests.size(); ++i) {
    auto quest_node = current_quests[i].GetCurrentQuestNode();
    if (quest_node) {
      if (CheckCondition(quest_node)) {
        current_quests[i].MoveToNextQuestNode();
      }
    } else {
      FinishQuest(current_quests[i].GetId());
      --i;
    }
  }
}

bool QuestController::CheckCondition(const QuestNode* quest_node) {
  auto params = quest_node->GetParams();
  switch (quest_node->GetType()) {
    case QuestNode::Type::kMoveToDestination: {
      Point destination = {params[0].toDouble(),
                           params[1].toDouble(),
                           params[2].toDouble()};
      return CheckMoveToDestination(destination);
    }
    default: {
      qDebug() << "Unhandled Type";
      return false;
    }
  }
}

bool QuestController::CheckMoveToDestination(const Point& destination) {
  return (model_->GetHero().GetCoordinates().GetRounded() ==
          destination.GetRounded());
}
