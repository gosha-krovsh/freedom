#ifndef VIEW_GAME_WIDGET_H_
#define VIEW_GAME_WIDGET_H_

#include <QOpenGLWidget>

#include <algorithm>
#include <unordered_set>
#include <memory>

#include "Model/model.h"

class GameWidget : public QOpenGLWidget {
  Q_OBJECT

 public:
  explicit GameWidget(const std::shared_ptr<Model>& model);

 private:
  void paintEvent(QPaintEvent*) override;
  void CenterCameraOnHero(QPainter* camera) const;

 private:
  std::shared_ptr<Model> model_;
};

#endif  // VIEW_GAME_WIDGET_H_
