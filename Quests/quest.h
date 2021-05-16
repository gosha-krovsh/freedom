#ifndef QUESTS_QUEST_H_
#define QUESTS_QUEST_H_

#include <QString>

#include <vector>
#include <memory>

#include "quest_node.h"
#include "GameObject/action.h"

class Quest {
 public:
  Quest(int id, const QString& name,
        const std::vector<QuestNode>& quest_nodes,
        const std::vector<Action>& start_actions,
        const std::vector<Action>& finish_actions);
  int GetId() const;
  QString GetName() const;
  const QuestNode* GetCurrentQuestNode() const;
  void MoveToNextQuestNode();
  std::vector<Action> GetStartActions() const;

 private:
  int id_;
  QString name_;
  std::vector<QuestNode> quest_nodes_;
  int current_node_index_{0};
  std::vector<Action> start_actions_;
  std::vector<Action> finish_actions_;
};

#endif  // QUESTS_QUEST_H_
