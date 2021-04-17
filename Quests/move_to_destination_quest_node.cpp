#include "move_to_destination_quest_node.h"

MoveToDestinationQuestNode::MoveToDestinationQuestNode(
    int id, const std::string& name, const Point& destination) :
    AbstractQuestNode(id, name), destination_(destination) {}

AbstractQuestNode::QuestNodeType
    MoveToDestinationQuestNode::GetQuestNodeType() const {
  return AbstractQuestNode::QuestNodeType::kMoveToDestination;
}

Point MoveToDestinationQuestNode::GetDestination() const {
  return destination_;
}
