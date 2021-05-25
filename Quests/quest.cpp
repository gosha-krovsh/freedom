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

int Quest::GetCurrentQuestNodeIndex() const {
  return current_node_index_;
}

void Quest::MoveToNextQuestNode() {
  ++current_node_index_;
}

std::vector<QString> Quest::GetQuestNodesNames() const {
  std::vector<QString> result;
  for (const auto& quest_node : quest_nodes_) {
    result.emplace_back(quest_node.GetName());
  }
  return result;
}
