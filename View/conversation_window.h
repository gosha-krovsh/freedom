#ifndef VIEW_CONVERSATION_WINDOW_H_
#define VIEW_CONVERSATION_WINDOW_H_

#include <QApplication>
#include <QAction>
#include <QToolButton>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFile>
#include <QScrollArea>
#include <QStyle>

#include <memory>
#include <vector>

#include "Controller/abstract_controller.h"

class ConversationWindow : public QWidget {
  Q_OBJECT

 public:
  ConversationWindow(const std::shared_ptr<Conversation>& conversation,
                     AbstractController* controller,
                     QWidget* parent = nullptr);
  ~ConversationWindow() override = default;

 private:
  void resizeEvent(QResizeEvent*) override;

  void SetUi();
  void SetStyles();
  void AddNextNode(int answer_index = -1);

  QToolButton* CreateCloseWidgetButton();
  QLabel* CreateConversationLabel(const QString& text);
  QPushButton* CreateAnswerButton(int answer_index, const QString& answer_text);
  QPushButton* CreateFinishConversationButton();
  void AnswerButtonPress(const std::vector<QPushButton*>& ans_buttons,
                         int answer_index);

 private:
  std::shared_ptr<Conversation> conversation_;
  AbstractController* controller_;

  QScrollArea* scroll_area_;
  QWidget* content_;
  QVBoxLayout* layout_;
};

#endif  // VIEW_CONVERSATION_WINDOW_H_
