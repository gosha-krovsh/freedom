#ifndef QUESTS_MOVE_TO_DESTINATION_QUEST_NODE_H_
#define QUESTS_MOVE_TO_DESTINATION_QUEST_NODE_H_

#include <GameObject/point.h>
#include "abstract_quest_node.h"

class MoveToDestinationQuestNode : public AbstractQuestNode {
 public:
  MoveToDestinationQuestNode(int id, const std::string& name,
                             const Point& destination);
  ~MoveToDestinationQuestNode() override = default;

  QuestNodeType GetQuestNodeType() const override;
  Point GetDestination() const;

 private:
  Point destination_;
};

#endif  // QUESTS_MOVE_TO_DESTINATION_QUEST_NODE_H_
