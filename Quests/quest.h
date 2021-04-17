#ifndef QUESTS_QUEST_H_
#define QUESTS_QUEST_H_

#include <QString>

#include <vector>
#include <memory>

#include "abstract_quest_node.h"

class Quest {
 public:
  Quest(int id, const QString& name,
        const std::vector<std::shared_ptr<AbstractQuestNode>>& quest_nodes);

 private:
  int id_;
  QString name_;
  std::vector<std::shared_ptr<AbstractQuestNode>> quest_nodes_;
  int current_node_index_{0};
};

#endif  // QUESTS_QUEST_H_
