#include <QKeyEvent>

#include "view.h"
#include "../Model/constants.h"

View::View(AbstractController* controller) : controller_(controller),
                                             timer_(new QTimer(this)) {
  setMinimumSize(constants::kWindowWidth, constants::kWindowHeight);

  connect(timer_, &QTimer::timeout, this, &View::Tick);
  timer_->start(1000/constants::kFPS);

  show();
}

void View::paintEvent(QPaintEvent*) {
  QPainter painter(this);

  const auto& map = controller_->GetMap();
  for (int z = map.size() - 1; z >= 0; --z) {
    for (int y = 0; y < map[z].size(); ++y) {
      for (int x = 0; x < map[z][y].size(); ++x) {
        if (map[z][y][x]) {
          map[z][y][x]->Draw(&painter);
        }
      }
    }
  }

  controller_->GetHero().Draw(&painter);
}

void View::Tick() {
  controller_->GetHero().Move();
  QWidget::update();
}

void View::keyPressEvent(QKeyEvent* event) {
  if (event->text() == "w") {
    controller_->UpKeyPressed();
  } else if (event->text() == "s") {
    controller_->DownKeyPressed();
  } else if (event->text() == "a") {
    controller_->LeftKeyPressed();
  } else if (event->text() == "d") {
    controller_->RightKeyPressed();
  }
}
void View::keyReleaseEvent(QKeyEvent* event) {
  if (event->text() == "w") {
    controller_->UpKeyRelease();
  } else if (event->text() == "s") {
    controller_->DownKeyRelease();
  } else if (event->text() == "a") {
    controller_->LeftKeyRelease();
  } else if (event->text() == "d") {
    controller_->RightKeyRelease();
  }
}
