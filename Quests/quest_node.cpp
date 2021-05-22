#include "quest_node.h"

QuestNode::QuestNode(const QString& name, const QString& type_str,
                     const std::vector<QString>& params) :
                     name_(name), params_(params) {
  SetType(type_str);
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
