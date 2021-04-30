#include "conversation.h"

Conversation::Conversation(int id, const std::vector<Node>& nodes) :
    id_(id), nodes_(nodes) {}

Conversation::Node Conversation::GetCurrentNode() const {
  return nodes_[current_node_index_];
}

void Conversation::MoveToNextNode(int answer_index) {
  current_node_index_ = nodes_[current_node_index_].
                        answers.at(answer_index).next_node_id;
}
