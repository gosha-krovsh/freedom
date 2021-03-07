#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include <QMainWindow>
#include <QTimer>

#include "../Controller/abstract_controller.h"

class View : public QMainWindow {
  Q_OBJECT

 public:
  explicit View(AbstractController* controller);

 private:
  void paintEvent(QPaintEvent*) override;
  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;
  void Tick();

  QTimer* timer_;

  AbstractController* controller_;
};

#endif  // VIEW_VIEW_H_
