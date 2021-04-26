#ifndef CONTROLLER_QUEST_CONTROLLER_H_
#define CONTROLLER_QUEST_CONTROLLER_H_

#include <memory>

#include "Model/model.h"

class QuestController {
 public:
  explicit QuestController(const std::shared_ptr<Model>& model);

  // Checks each tick, if there is a current quest, and if it is, checks
  // the condition of a current node in this quest. If all quest nodes were
  // accomplished, it finishes the current quest.
  void Tick(int current_tick);

  void StartQuest(int id);

 private:
  // Returns true, if the condition, needed to accomplish |quest_node|, is met.
  bool CheckCondition(const std::shared_ptr<QuestNode>& quest_node);
  bool CheckMoveToDestinationCondition(const Point& destination);

 private:
  std::shared_ptr<Model> model_;
};

#endif  // CONTROLLER_QUEST_CONTROLLER_H_
