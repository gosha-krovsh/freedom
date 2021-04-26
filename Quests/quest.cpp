#include "quest.h"

Quest::Quest(int id, const QString& name,
             const std::vector<QuestNode>& quest_nodes) :
             id_(id), name_(name), quest_nodes_(quest_nodes) {}

int Quest::GetId() const {
  return id_;
}

QString Quest::GetName() const {
  return name_;
}

const QuestNode* Quest::GetCurrentQuestNode() const {
  if (current_node_index_ >= quest_nodes_.size()) {
    return nullptr;
  }
  return &quest_nodes_[current_node_index_];
}

void Quest::MoveToNextQuestNode() {
  ++current_node_index_;
}
