#ifndef QUEST_TASK_LIST_H
#define QUEST_TASK_LIST_H

#include <QScrollArea>
#include <QLabel>

#include "Controller/abstract_controller.h"
#include "Quests/quest.h"

class QuestTaskList : public QWidget {
  Q_OBJECT

 public:
  QuestTaskList(AbstractController* controller,
                     QWidget* parent = nullptr);
  ~QuestTaskList() override = default;

 private:
  void resizeEvent(QResizeEvent*) override;
  void keyPressEvent(QKeyEvent*) override;

  void SetUi();
  void SetStyles();
  void AddNextNode(int answer_index = -1);

  QLabel* CreateConversationLabel(const QString& text);
  void UpdateCurrentLables();

 private:
  Conversation conversation_;
  AbstractController* controller_;

  QScrollArea* scroll_area_;
  QWidget* content_;
  QVBoxLayout* layout_;

  std::vector<QString> node_strings_;
};

#endif  // QUEST_TASK_LIST_H
