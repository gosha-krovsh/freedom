#ifndef QUESTS_ABSTRACT_QUEST_NODE_H_
#define QUESTS_ABSTRACT_QUEST_NODE_H_

#include <QString>

class AbstractQuestNode {
 public:
  enum class QuestNodeType {
    kMoveToDestination
  };

 public:
  AbstractQuestNode(int id, const QString& name);
  virtual ~AbstractQuestNode() = default;

  virtual QuestNodeType GetQuestNodeType() const = 0;

  int GetId() const;
  QString GetName() const;

 private:
  int id_;
  QString name_;
};

#endif  // QUESTS_ABSTRACT_QUEST_NODE_H_
