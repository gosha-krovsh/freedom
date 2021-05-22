#ifndef CONTROLLER_QUEST_CONTROLLER_H_
#define CONTROLLER_QUEST_CONTROLLER_H_

#include <memory>

#include "abstract_controller.h"
#include "Model/model.h"

class QuestController {
 public:
  QuestController(AbstractController* controller,
                  const std::shared_ptr<Model>& model);

  // Checks each tick the condition of the current node of every quest in
  // |Model.current_quests|. If all quest nodes in some quest were
  // accomplished, it finishes this quest.
  void Tick(int current_tick);

  void StartQuest(int id);

 private:
  void FinishQuest(int id);

  // Returns true, if the condition, needed to accomplish |quest_node|, is met.
  bool CheckCondition(const QuestNode* quest_node);
  bool CheckMoveToDestination(const Point& destination);

 private:
  AbstractController* controller_;
  std::shared_ptr<Model> model_;
};

#endif  // CONTROLLER_QUEST_CONTROLLER_H_
