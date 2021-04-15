#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include <QKeyEvent>
#include <QMainWindow>
#include <QTimer>

#include <memory>
#include <utility>

#include "View/item_bar.h"
#include "Controller/abstract_controller.h"
#include "Model/model.h"

class View : public QMainWindow {
  Q_OBJECT

 public:
  View(AbstractController* controller, std::shared_ptr<Model> model);

  std::pair<ItemBar*, ItemBar*> GetSrcDestBars(int id);

 private:
  void paintEvent(QPaintEvent*) override;
  void keyPressEvent(QKeyEvent*) override;
  void keyReleaseEvent(QKeyEvent*) override;
  void changeEvent(QEvent*) override;
  void TimerEvent();

  void SetStyles();
  void CenterCameraOnHero(QPainter* camera) const;

 private:
  QTimer* timer_;
  AbstractController* controller_;
  std::shared_ptr<Model> model_;

  bool is_item_dialog_open_;

  ItemBar* hero_item_bar_;
  ItemBar* object_item_bar_;
};

#endif  // VIEW_VIEW_H_
