#include "view.h"

View::View(AbstractController* controller, std::shared_ptr<Model> model) :
    controller_(controller),
    model_(model),
    timer_(new QTimer(this)),
    is_item_dialog_open_(false),
    hero_item_bar_(new ItemBar(constants::kWindowWidth / 4,
                               4 * constants::kWindowHeight / 5,
                               constants::kWindowWidth / 2,
                               constants::kWindowHeight / 5,
                               0,
                               controller,
                               this,
                               &model_->GetHero())),
    object_item_bar_(new ItemBar(constants::kWindowWidth / 4,
                               3 * constants::kWindowHeight / 5,
                               constants::kWindowWidth / 2,
                               constants::kWindowHeight / 5,
                               1,
                               controller,
                               this)){
  setMinimumSize(constants::kWindowWidth, constants::kWindowHeight);
  SetStyles();
  show();

  connect(timer_, &QTimer::timeout, this, &View::TimerEvent);
  timer_->start(1000 / constants::kFPS);

  hero_item_bar_->Show();
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
      // Opens the second bar, when clicked,
      // and there is an object that can store something nearby
      StorableObject* obj = controller_->CheckStorableBlocks();

      if (!is_item_dialog_open_ && obj) {
        is_item_dialog_open_ = true;
        hero_item_bar_->SetEnabled(true);

        object_item_bar_->Show();
        object_item_bar_->SetEnabled(true);
        object_item_bar_->AssignObject(obj);
      } else {
        is_item_dialog_open_ = false;
        hero_item_bar_->SetEnabled(false);

        object_item_bar_->Hide();
        object_item_bar_->SetEnabled(false);
      }

      hero_item_bar_->UpdateIcons();
      object_item_bar_->UpdateIcons();
      break;
    }
    // Following keys are used to use items,
    // this feature will be updated in future
    case Qt::Key_1 : {
      hero_item_bar_->UseItem(0);
      break;
    }
    case Qt::Key_2 : {
      hero_item_bar_->UseItem(1);
      break;
    }
    case Qt::Key_3 : {
      hero_item_bar_->UseItem(2);
      break;
    }
    case Qt::Key_4 : {
      hero_item_bar_->UseItem(3);
      break;
    }
    case Qt::Key_5 : {
      hero_item_bar_->UseItem(4);
      break;
    }
    case Qt::Key_6 : {
      hero_item_bar_->UseItem(5);
      break;
    }
    case Qt::Key_7 : {
      hero_item_bar_->UseItem(6);
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

void View::SetStyles() {
  QFile styleFile(":styles.qss");
  styleFile.open(QFile::ReadOnly);
  QString style(styleFile.readAll());

  setStyleSheet(style);
  styleFile.close();
}

std::pair<ItemBar*, ItemBar*> View::GetSrcDestBars(int id) {
  // Makes a pair of 2 bars, where first argument is a source
  // and second is a destination
  switch (id) {
    case 0: return std::make_pair(hero_item_bar_, object_item_bar_);
    case 1: return std::make_pair(object_item_bar_, hero_item_bar_);
    default:
      return std::make_pair(nullptr, nullptr);
  }
}
