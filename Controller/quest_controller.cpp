#include "quest_controller.h"

QuestController::QuestController(AbstractController* controller,
                                 const std::shared_ptr<Model>& model) :
                                 controller_(controller),
                                 model_(model) {}

void QuestController::StartQuest(int id) {
  model_->AddCurrentQuest(id);

  const Quest* quest = model_->GetCurrentQuestById(id);
  controller_->ExecuteActions(quest->GetStartActions());
  controller_->AddQuestToList(quest->GetName(),
                              quest->GetQuestNodesNames());
  qDebug() << "Quest started";  // message to test
}

void QuestController::FinishQuest(int id) {
  const Quest* quest = model_->GetCurrentQuestById(id);
  if (quest) {
    controller_->ExecuteActions(quest->GetFinishActions());
    quest = model_->GetCurrentQuestById(id);  // iterator invalidate if not this
    controller_->DeleteQuestFromList(quest->GetName());
    model_->EraseCurrentQuest(id);
    qDebug() << "Quest finished";  // message to test
  }
}

void QuestController::Tick(int) {
  auto& current_quests = model_->GetCurrentQuests();
  for (int i = 0; i < current_quests.size(); ++i) {
    auto quest_node = current_quests[i].GetCurrentQuestNode();
    if (quest_node) {
      if (CheckCondition(quest_node)) {
        current_quests[i].MoveToNextQuestNode();
        controller_->UpdateQuestList(current_quests[i].GetName(),
                     current_quests[i].GetCurrentQuestNodeIndex());
        qDebug() << "Quest node completed";  // message to test
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
    case QuestNode::Type::kTakeItem: {
      int item_id = params[0].toInt();
      return CheckTakeItem(item_id);
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

bool QuestController::CheckTakeItem(int item_id) {
  return model_->GetHero().HasItem(static_cast<Item::Type>(item_id));
}
