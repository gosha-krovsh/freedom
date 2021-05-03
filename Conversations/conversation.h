#ifndef CONVERSATIONS_CONVERSATION_H_
#define CONVERSATIONS_CONVERSATION_H_

#include <QDebug>
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
  Conversation() = default;
  Conversation(int id, const std::vector<Node>& nodes);

  Node GetCurrentNode() const;
  bool IsLastNode() const;
  std::vector<int> GetAnswersIndexesHistory() const;
  void MoveToNextNode(int answer_index);

  void Reset();

 private:
  int id_;
  std::vector<Node> nodes_;
  int current_node_id_{0};
  std::vector<int> answers_indexes_history_{};
};

#endif  // CONVERSATIONS_CONVERSATION_H_
