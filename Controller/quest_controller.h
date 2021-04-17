#ifndef CONTROLLER_QUEST_CONTROLLER_H_
#define CONTROLLER_QUEST_CONTROLLER_H_

#include <memory>

#include "Model/model.h"

class QuestController {
 public:
  explicit QuestController(const std::shared_ptr<Model>& model);
  void Tick(int current_tick);
  void StartQuest(int id);

 private:
  bool CheckCondition(const std::shared_ptr<AbstractQuestNode>& quest_node);
  bool CheckCondition(
      const std::shared_ptr<MoveToDestinationQuestNode>& quest_node);

 private:
  std::shared_ptr<Model> model_;
};

#endif  // CONTROLLER_QUEST_CONTROLLER_H_
