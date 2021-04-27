#include "view.h"

View::View(AbstractController* controller, std::shared_ptr<Model> model) :
    controller_(controller),
    model_(model),
    timer_(new QTimer(this)),
    is_item_dialog_open_(false),
    item_bar_pack_(new BarPack(constants::kWindowWidth / 2,
                               3 * constants::kWindowHeight / 5,
                               constants::kWindowWidth / 2,
                               2 * constants::kWindowHeight / 5,
                               controller,
                               this,
                               &model_->GetHero())) {
  setMinimumSize(constants::kWindowWidth, constants::kWindowHeight);
  show();

  connect(timer_, &QTimer::timeout, this, &View::TimerEvent);
  timer_->start(1000 / constants::kFPS);

  item_bar_pack_->show();
}

void View::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  CenterCameraOnHero(&painter);

  const Hero& hero = model_->GetHero();
  const auto& map = model_->GetMap();
  for (int z = 0; z < map.size(); ++z) {
    for (int y = 0; y < map[z].size(); ++y) {
      for (int x = 0; x < map[z][y].size(); ++x) {
        if (map[z][y][x]) {
          map[z][y][x]->Draw(&painter);
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
    case Qt::Key_E: {
      // Opens the second bar, when clicked
      // and there is an object that can store something nearby
      StorableObject* obj = controller_->GetStorableBlocksAround();

      if (!is_item_dialog_open_ && obj) {
        is_item_dialog_open_ = true;
        item_bar_pack_->GetHeroBar()->setEnabled(true);

        item_bar_pack_->GetObjectBar()->show();
        item_bar_pack_->GetObjectBar()->setEnabled(true);
        item_bar_pack_->GetObjectBar()->AssignObject(obj);
      } else {
        is_item_dialog_open_ = false;
        item_bar_pack_->GetHeroBar()->setEnabled(false);

        item_bar_pack_->GetObjectBar()->hide();
        item_bar_pack_->GetObjectBar()->setEnabled(false);
      }
      break;
    }
      // Following keys are used to use items,
      // this feature will be updated in future
    case Qt::Key_1 :
    case Qt::Key_2 :
    case Qt::Key_3 :
    case Qt::Key_4 :
    case Qt::Key_5 :
    case Qt::Key_6 :
    case Qt::Key_7 : {
      item_bar_pack_->GetHeroBar()->UseItem(event->key() - Qt::Key_1);
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

void View::resizeEvent(QResizeEvent*) {
  item_bar_pack_->SetCenterGeometry(width() / 2,
                                    height() - 2 * constants::kWindowHeight / 5,
                                    constants::kWindowWidth / 2,
                                    2 * constants::kWindowHeight / 5);
}

std::pair<ItemBar*, ItemBar*> View::GetSrcDestBars(int id) {
  // Makes a pair of 2 bars, where first argument is a source
  // and second is a destination
  switch (id) {
    case 0: return std::make_pair(item_bar_pack_->GetHeroBar(), item_bar_pack_->GetObjectBar());
    case 1: return std::make_pair(item_bar_pack_->GetObjectBar(), item_bar_pack_->GetHeroBar());
    default:return std::make_pair(nullptr, nullptr);
  }
}
