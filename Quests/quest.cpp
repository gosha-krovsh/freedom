#include "quest.h"

Quest::Quest(int id, const QString& name,
             const std::vector<QuestNode>& quest_nodes,
             const std::vector<Action>& start_actions,
             const std::vector<Action>& finish_actions) :
    id_(id), name_(name), quest_nodes_(quest_nodes),
    start_actions_(start_actions),
    finish_actions_(finish_actions) {}

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

std::vector<Action> Quest::GetStartActions() const {
  return start_actions_;
}

std::vector<Action> Quest::GetFinishActions() const {
  return finish_actions_;
}
