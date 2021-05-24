#ifndef CONVERSATIONS_CONVERSATION_H_
#define CONVERSATIONS_CONVERSATION_H_

#include <QDebug>
#include <QString>

#include <memory>
#include <vector>

#include "GameObject/action.h"

class Conversation {
 public:
  struct Answer {
    QString GetFormattedText() const;

    QString text;
    int next_node_id;
    std::vector<Action> actions;
    // std::vector<std::shared_ptr<Action>> actions;
    // std::shared_ptr<Action> action{nullptr};
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
  void MoveToNextNode(int answer_index);

 private:
  void SetNodes(const std::vector<Node>& nodes);

  int id_;
  std::vector<Node> nodes_;
  int current_node_index_{0};
};

#endif  // CONVERSATIONS_CONVERSATION_H_
