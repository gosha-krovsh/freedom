#include "quest_node.h"

QuestNode::QuestNode(int id, const QString& name, Type type,
                     const std::vector<QString>& params) :
                     id_(id), name_(name), type_(type), params_(params) {}

int QuestNode::GetId() const {
  return id_;
}

QString QuestNode::GetName() const {
  return name_;
}

QuestNode::Type QuestNode::GetType() const {
  return type_;
}

std::vector<QString> QuestNode::GetParams() const {
  return params_;
}
