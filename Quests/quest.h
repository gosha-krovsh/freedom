#ifndef QUESTS_QUEST_H_
#define QUESTS_QUEST_H_

#include <QString>

#include <vector>
#include <memory>

#include "quest_node.h"

class Quest {
 public:
  Quest(int id, const QString& name,
        const std::vector<QuestNode>& quest_nodes);
  int GetId() const;
  QString GetName() const;
  const QuestNode* GetCurrentQuestNode() const;
  void MoveToNextQuestNode();

 private:
  int id_;
  QString name_;
  std::vector<QuestNode> quest_nodes_;
  int current_node_index_{0};
};

#endif  // QUESTS_QUEST_H_
