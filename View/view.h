#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include <QKeyEvent>
#include <QMainWindow>
#include <QTimer>
#include <memory>
#include <unordered_set>
#include <utility>

#include "Controller/abstract_controller.h"
#include "Model/model.h"
#include "GameObject/object.h"

class View : public QMainWindow {
  Q_OBJECT

 public:
  View(AbstractController* controller, const std::shared_ptr<Model>& model);

 private:
  void paintEvent(QPaintEvent*) override;
  void keyPressEvent(QKeyEvent*) override;
  void keyReleaseEvent(QKeyEvent*) override;
  void changeEvent(QEvent*) override;
  void TimerEvent();

  void CenterCameraOnHero(QPainter* camera) const;

 private:
  QTimer* timer_;
  AbstractController* controller_;
  std::shared_ptr<Model> model_;
};

#endif  // VIEW_VIEW_H_
