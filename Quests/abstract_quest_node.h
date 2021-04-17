#ifndef QUESTS_ABSTRACT_QUEST_NODE_H_
#define QUESTS_ABSTRACT_QUEST_NODE_H_

#include <string>

class AbstractQuestNode {
 public:
  enum class QuestNodeType {
    kMoveToDestination
  };

 public:
  AbstractQuestNode(int id, const std::string& name);
  virtual ~AbstractQuestNode() = default;

  virtual QuestNodeType GetQuestNodeType() const = 0;

  int GetId() const;
  std::string GetName() const;

 private:
  int id_;
  std::string name_;
};

#endif  // QUESTS_ABSTRACT_QUEST_NODE_H_
