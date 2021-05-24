#include "conversation.h"

Conversation::Conversation(int id, const std::vector<Node>& nodes) : id_(id) {
  SetNodes(nodes);
}

void Conversation::SetNodes(const std::vector<Node>& nodes) {
  if (nodes.empty()) {
    qDebug() << "Conversation must contain at least 1 node";
  }
  int max_id = std::max_element(nodes.begin(), nodes.end(),
                                [](const Node& lhs, const Node& rhs) {
    return lhs.id < rhs.id;
  })->id;

  nodes_ = std::vector<Node>(max_id + 1);
  for (auto& node : nodes) {
    nodes_[node.id] = node;
  }
}

Conversation::Node Conversation::GetCurrentNode() const {
  return nodes_[current_node_index_];
}

void Conversation::MoveToNextNode(int answer_index) {
  current_node_index_ = nodes_[current_node_index_].
                        answers.at(answer_index).next_node_id;
}

bool Conversation::IsLastNode() const {
  return nodes_[current_node_index_].answers.empty();
}
