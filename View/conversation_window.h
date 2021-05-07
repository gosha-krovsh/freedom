#ifndef VIEW_CONVERSATION_WINDOW_H_
#define VIEW_CONVERSATION_WINDOW_H_

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFile>
#include <QScrollArea>
#include <QStyle>
#include <QKeyEvent>

#include <vector>

#include "Controller/abstract_controller.h"

class ConversationWindow : public QWidget {
  Q_OBJECT

 public:
  ConversationWindow(const Conversation& conversation,
                     AbstractController* controller,
                     QWidget* parent = nullptr);
  ~ConversationWindow() override = default;

 private:
  void resizeEvent(QResizeEvent*) override;
  void keyPressEvent(QKeyEvent*) override;

  void SetUi();
  void SetStyles();
  void AddNextNode(int answer_index = -1);

  QLabel* CreateConversationLabel(const QString& text);
  QPushButton* CreateAnswerButton(int answer_index, const QString& answer_text);
  QPushButton* CreateFinishConversationButton();
  void AnswerButtonPress(int answer_index);

 private:
  Conversation conversation_;
  AbstractController* controller_;

  QScrollArea* scroll_area_;
  QWidget* content_;
  QVBoxLayout* layout_;
  std::vector<QPushButton*> current_ans_buttons_;
};

#endif  // VIEW_CONVERSATION_WINDOW_H_
