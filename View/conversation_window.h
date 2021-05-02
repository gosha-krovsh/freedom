#ifndef VIEW_CONVERSATION_WINDOW_H_
#define VIEW_CONVERSATION_WINDOW_H_

#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFile>
#include <QScrollArea>
#include <QStyle>

#include <Controller/abstract_controller.h>

class ConversationWindow : public QWidget {
  Q_OBJECT
 public:
  ConversationWindow(const Conversation& conversation,
                     AbstractController* controller,
                     QWidget* parent = nullptr);
  ~ConversationWindow() override = default;

 private:
  void resizeEvent(QResizeEvent*) override;

  void SetStyles();
  void SetUi();
  void AddNode(int answer_index = -1);

  Conversation conversation_;
  AbstractController* controller_;

  QScrollArea* scroll_area_;
  QWidget* content_;
  QVBoxLayout* layout_;
};

#endif  // VIEW_CONVERSATION_WINDOW_H_
