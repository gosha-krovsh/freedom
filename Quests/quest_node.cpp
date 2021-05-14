#include "quest_node.h"

QuestNode::QuestNode(int id, const QString& name, const QString& type_str,
                     const std::vector<QString>& params) :
                     id_(id), name_(name), params_(params) {
  SetType(type_str);
}

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

void QuestNode::SetType(const QString& type_str) {
  if (type_str == "MoveToDestination") {
    type_ = Type::kMoveToDestination;
  } else {
    qDebug() << "Invalid QuestNode type";
  }
}
