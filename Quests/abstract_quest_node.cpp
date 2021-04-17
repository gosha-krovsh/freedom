#include "abstract_quest_node.h"

AbstractQuestNode::AbstractQuestNode(int id, const QString& name) :
    id_(id), name_(name) {}

int AbstractQuestNode::GetId() const {
  return id_;
}

QString AbstractQuestNode::GetName() const {
  return name_;
}
