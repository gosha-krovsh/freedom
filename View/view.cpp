#include <QKeyEvent>

#include "view.h"
#include "../Model/constants.h"

View::View(AbstractController* controller,
           Model* model) : controller_(controller),
                           model_(model),
                           timer_(new QTimer(this)) {
  setMinimumSize(constants::kWindowWidth, constants::kWindowHeight);

  connect(timer_, &QTimer::timeout, this, &View::TimerEvent);
  timer_->start(1000/constants::kFPS);

  show();
}

void View::paintEvent(QPaintEvent*) {
  QPainter painter(this);

  const auto& map = model_->GetMap();
  for (int z = map.size() - 1; z >= 0; --z) {
    for (int y = 0; y < map[z].size(); ++y) {
      for (int x = 0; x < map[z][y].size(); ++x) {
        if (map[z][y][x]) {
          map[z][y][x]->Draw(&painter);
        }
      }
    }
  }

  model_->GetHero().Draw(&painter);
}

void View::TimerEvent() {
  controller_->Tick();
  repaint();
}

void View::keyPressEvent(QKeyEvent* event) {
  switch (event->key()) {
    case Qt::Key_Up:
    case Qt::Key_W: {
      controller_->SetControlUpKeyState(true);
      break;
    }
    case Qt::Key_Right:
    case Qt::Key_D: {
      controller_->SetControlRightKeyState(true);
      break;
    }
    case Qt::Key_Down:
    case Qt::Key_S: {
      controller_->SetControlDownKeyState(true);
      break;
    }
    case Qt::Key_Left:
    case Qt::Key_A: {
      controller_->SetControlLeftKeyState(true);
      break;
    }
  }
}

void View::keyReleaseEvent(QKeyEvent* event) {
  switch (event->key()) {
    case Qt::Key_Up:
    case Qt::Key_W: {
      controller_->SetControlUpKeyState(false);
      break;
    }
    case Qt::Key_Right:
    case Qt::Key_D: {
      controller_->SetControlRightKeyState(false);
      break;
    }
    case Qt::Key_Down:
    case Qt::Key_S: {
      controller_->SetControlDownKeyState(false);
      break;
    }
    case Qt::Key_Left:
    case Qt::Key_A: {
      controller_->SetControlLeftKeyState(false);
      break;
    }
  }
}
