#ifndef QUEST_TASK_LIST_H
#define QUEST_TASK_LIST_H

#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QLabel>
#include <QFile>

#include "Controller/abstract_controller.h"
#include "Quests/quest.h"

class QuestTaskList : public QWidget {
  Q_OBJECT

 public:
  QuestTaskList(AbstractController* controller,
                     QWidget* parent = nullptr);

  void SetQuestString(const QString& quest_name,
                      const std::vector<QString>& node_strings);
  void UpdateCurrentLables(const QString& quest_name, int index);
  void DeleteQuest(const QString& quest);

 private:
  void resizeEvent(QResizeEvent*) override;

  void SetUi();
  void SetStyles();

 private:
  Conversation conversation_;
  AbstractController* controller_;

  QScrollArea* scroll_area_;
  QWidget* content_;
  QVBoxLayout* layout_;

  std::map<QString, std::vector<QString>> quest_string_;
  std::map<QString, std::pair<QLabel*, std::vector<QLabel*>>> quest_labels_;
};

#endif  // QUEST_TASK_LIST_H
