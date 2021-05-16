#ifndef QUESTS_QUEST_NODE_H_
#define QUESTS_QUEST_NODE_H_

#include <QString>
#include <QDebug>

#include <vector>

class QuestNode {
 public:
  enum class Type {
    kMoveToDestination
  };

 public:
  QuestNode(const QString& name, const QString& type_str,
            const std::vector<QString>& params);

  QString GetName() const;
  Type GetType() const;
  std::vector<QString> GetParams() const;

 private:
  void SetType(const QString& type_str);

  QString name_;
  Type type_;
  std::vector<QString> params_;
};

#endif  // QUESTS_QUEST_NODE_H_
