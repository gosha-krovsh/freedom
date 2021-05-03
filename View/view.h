#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include <QKeyEvent>
#include <QMainWindow>
#include <QTimer>

#include <algorithm>
#include <memory>
#include <unordered_set>
#include <utility>

#include "conversation_window.h"
#include "Controller/abstract_controller.h"
#include "Model/model.h"
#include "GameObject/object.h"

class View : public QMainWindow {
  Q_OBJECT

 public:
  View(AbstractController* controller, const std::shared_ptr<Model>& model);
  void CloseConversationWindow();

 private:
  void paintEvent(QPaintEvent*) override;
  void keyPressEvent(QKeyEvent*) override;
  void keyReleaseEvent(QKeyEvent*) override;
  void changeEvent(QEvent*) override;
  void resizeEvent(QResizeEvent*) override;
  void TimerEvent();

  void CenterCameraOnHero(QPainter* camera) const;
  bool IsInputBlocked() const;
  void InterruptAllInput();

 private:
  QTimer* timer_;
  AbstractController* controller_;
  std::shared_ptr<Model> model_;

  std::unique_ptr<ConversationWindow> conversation_window_{nullptr};
};

#endif  // VIEW_VIEW_H_
