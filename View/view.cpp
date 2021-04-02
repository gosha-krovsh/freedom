#include "view.h"

View::View(AbstractController* controller,
           std::shared_ptr<Model> model) : controller_(controller),
                                           model_(std::move(model)),
                                           timer_(new QTimer(this)) {
  setMinimumSize(constants::kWindowWidth, constants::kWindowHeight);

  connect(timer_, &QTimer::timeout, this, &View::TimerEvent);
  timer_->start(1000 / constants::kFPS);

  show();
}

void View::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  CenterCameraOnHero(&painter);

  const Hero& hero = model_->GetHero();
  const GameMap& map = model_->GetMap();
  std::unordered_set<const Object*> transparent_blocks{
    map.GetTransparentBlocks(hero.GetRoundedX(), hero.GetRoundedY())};

  for (int z = 0; z < map.GetZSize(); ++z) {
    for (int y = 0; y < map.GetYSize(); ++y) {
      for (int x = 0; x < map.GetXSize(); ++x) {
        auto curr_block = map.GetBlock(x, y, z);
        if (curr_block) {
          if (transparent_blocks.find(curr_block) != transparent_blocks.end()) {
            painter.setOpacity(constants::kBlockOpacity);
          }
          curr_block->Draw(&painter);
          painter.setOpacity(1);
        }

        if (hero.GetRoundedX() == x &&
            hero.GetRoundedY() == y &&
            hero.GetRoundedZ() == z) {
          hero.Draw(&painter);
        }
      }
    }
  }
}

void View::CenterCameraOnHero(QPainter* camera) const {
  // Get center of screen
  double x_camera_offset = width() / 2.;
  double y_camera_offset = height() / 2.;

  // Center camera on center of |Hero|
  x_camera_offset -= (model_->GetHero().GetCoordinates().GetIsometricX() + 1)
      * (constants::kSizeOfBlock / 2.);
  y_camera_offset -= (model_->GetHero().GetCoordinates().GetIsometricY() + 1)
      * (constants::kSizeOfBlock / 2.);

  // Make camera follow |Hero|
  camera->translate(x_camera_offset, y_camera_offset);
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

void View::changeEvent(QEvent* event) {
  if (event->type() == QEvent::ActivationChange && !isActiveWindow()) {
    controller_->SetControlUpKeyState(false);
    controller_->SetControlRightKeyState(false);
    controller_->SetControlDownKeyState(false);
    controller_->SetControlLeftKeyState(false);
  }
}
