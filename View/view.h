#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include <QKeyEvent>
#include <QMainWindow>
#include <QTimer>

#include "../Controller/abstract_controller.h"
#include "../Model/model.h"

class View : public QMainWindow {
  Q_OBJECT

 public:
  View(AbstractController* controller, std::shared_ptr<Model> model);

 private:
  void paintEvent(QPaintEvent*) override;
  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;
  void TimerEvent();

  QTimer* timer_;

  AbstractController* controller_;
  std::shared_ptr<Model> model_;
};

#endif  // VIEW_VIEW_H_
