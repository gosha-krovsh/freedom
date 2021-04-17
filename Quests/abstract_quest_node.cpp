#include "abstract_quest_node.h"

AbstractQuestNode::AbstractQuestNode(int id, const std::string& name) :
    id_(id), name_(name) {}

int AbstractQuestNode::GetId() const {
  return id_;
}

std::string AbstractQuestNode::GetName() const {
  return name_;
}
