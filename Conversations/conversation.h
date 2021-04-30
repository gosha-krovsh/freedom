#ifndef CONVERSATIONS_CONVERSATION_H_
#define CONVERSATIONS_CONVERSATION_H_

#include <QString>
#include <vector>

class Conversation {
 public:
  struct Answer {
    QString text;
    int next_node_id;
  };

  struct Node {
    int id;
    QString text;
    std::vector<Answer> answers;
  };

 public:
  Conversation(int id, const std::vector<Node>& nodes);
  Node GetCurrentNode() const;
  void MoveToNextNode(int answer_index);

 private:
  int id_;
  std::vector<Node> nodes_;
  int current_node_index_{0};
};

#endif  // CONVERSATIONS_CONVERSATION_H_
