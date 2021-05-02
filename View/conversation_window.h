#ifndef VIEW_CONVERSATION_WINDOW_H_
#define VIEW_CONVERSATION_WINDOW_H_

#include <QWidget>
#include <QGridLayout>

#include <Controller/abstract_controller.h>
#include <QLabel>
#include <QFile>
#include <QScrollArea>

class ConversationWindow : public QWidget {
  Q_OBJECT
 public:
  ConversationWindow(const Conversation& conversation,
                     AbstractController* controller,
                     QWidget* parent = nullptr);
  ~ConversationWindow() override = default;

 private:
  void SetStyles();
  void SetUi();
  void resizeEvent(QResizeEvent*) override;

  Conversation conversation_;
  AbstractController* controller_;

  QScrollArea* scroll_area_;
  QWidget* content_;
  QGridLayout* layout_;
};

#endif  // VIEW_CONVERSATION_WINDOW_H_
