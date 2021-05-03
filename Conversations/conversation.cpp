#include "conversation.h"

Conversation::Conversation(int id, const std::vector<Node>& nodes) :
    id_(id), nodes_(nodes) {
  if (nodes.empty()) {
    qDebug() << "Conversation must contain at least 1 node";
  }
}

Conversation::Node Conversation::GetCurrentNode() const {
  return nodes_[current_node_id_];
}

std::vector<int> Conversation::GetAnswersIndexesHistory() const {
  return answers_indexes_history_;
}

void Conversation::MoveToNextNode(int answer_index) {
  answers_indexes_history_.emplace_back(answer_index);
  current_node_id_ = GetCurrentNode().answers.at(answer_index).next_node_id;
}

bool Conversation::IsLastNode() const {
  return GetCurrentNode().answers.empty();
}

void Conversation::Reset() {
  answers_indexes_history_.clear();
  current_node_id_ = 0;
}
