#include "view.h"

View::View(AbstractController* controller,
           const std::shared_ptr<Model>& model) :
    controller_(controller),
    model_(model),
    timer_(new QTimer(this)),
    item_bar_pack_(new BarPack(controller, model, this,
                               model_->GetHero().GetStorage(),
                               model_->GetHero().GetClothingStorage(),
                               model_->GetHero().GetGunStorage())),
    status_bar_(new StatusBar(model,
                              {StatusBar::Type::kHealth,
                               StatusBar::Type::kAttack},
                              this, constants::kStatusBarDefaultCenteredX,
                              0,
                              constants::kStatusBarDefaultWidth,
                              constants::kStatusBarDefaultHeight)){
  setMinimumSize(constants::kWindowWidth, constants::kWindowHeight);
  SetUi();
  SetStyles();

  show();

  connect(timer_, &QTimer::timeout, this, &View::TimerEvent);
  StartTickTimer();
  item_bar_pack_->show();
}

void View::SetUi() {
  // health_bar_->setObjectName("health_bar");
  // health_bar_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  // health_bar_->setText("❤");
  // health_bar_->setTextInteractionFlags(Qt::TextInteractionFlag::NoTextInteraction);
  // health_bar_->setGeometry(2 * constants::kWindowWidth / 85,
  //                          2 * constants::kWindowHeight / 50,
  //                          8 * constants::kWindowWidth / 85,
  //                          2 * constants::kWindowHeight / 50);
}

void View::SetStyles() {
  QFile styleFile(":view_styles");
  styleFile.open(QFile::ReadOnly);
  QString style(styleFile.readAll());

  setStyleSheet(style);
  styleFile.close();
}

void View::StartTickTimer() {
  timer_->start(1000 / constants::kFPS);
}

void View::StopTickTimer() {
  timer_->stop();
}

void View::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  CenterCameraOnHero(&painter);

  const Hero& hero = model_->GetHero();
  const GameMap& map = model_->GetMap();
  const auto& bots = model_->GetBots();
  std::unordered_set<const Object*>
      transparent_blocks = map.GetTransparentBlocks();

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

        bool hero_drown = false;
        Point camera = Point(map.GetXSize(), map.GetYSize());
        double hero_distance_to_camera =
            hero.GetCoordinates().DistanceFrom(camera);

        for (const auto& current_bot : bots) {
          double bot_distance_to_camera =
              current_bot.GetCoordinates().DistanceFrom(camera);

          if (hero.GetRoundedX() == x &&
              hero.GetRoundedY() == y &&
              hero.GetRoundedZ() == z &&
              hero_distance_to_camera > bot_distance_to_camera) {
            hero.Draw(&painter);
            hero_drown = true;
          }
          if (current_bot.GetRoundedX() == x &&
              current_bot.GetRoundedY() == y &&
              current_bot.GetRoundedZ() == z) {
            double dist = hero.GetCoordinates().
                               DistanceFrom(current_bot.GetCoordinates());

            if (!current_bot.IsAbleToAttack()) {
              painter.setOpacity(1);
            } else {
              painter.setOpacity(std::max(dist / 2,
                                          constants::kBotOpacity));
            }
            current_bot.Draw(&painter);
            painter.setOpacity(1);
          }
        }

        if (!hero_drown &&
            hero.GetRoundedX() == x &&
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
  if (IsInputBlocked()) {
    return;
  }

  switch (event->key()) {
    case Qt::Key_Space: {
      controller_->HeroAttack();
      break;
    }
    case Qt::Key_Q: {
      auto conversation = controller_->StartConversation();
      if (conversation) {
        StopTickTimer();
        conversation_window_ = std::make_unique<ConversationWindow>(
            *conversation, controller_, this);
        InterruptAllInput();
        resizeEvent(nullptr);

        item_bar_pack_->hide();
      }
      break;
    }
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
      ItemDialogEvent();
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
    InterruptAllInput();
  }
}

void View::resizeEvent(QResizeEvent*) {
  if (conversation_window_) {
    conversation_window_->setGeometry(
        constants::kXConversationWindowMultiplier * width(),
        constants::kYConversationWindowMultiplier * height(),
        constants::kWidthConversationWindowMultiplier * width(),
        constants::kHeightConversationWindowMultiplier * height());
  }
  item_bar_pack_->SetCenterGeometry(width() / 2,
                                    height() - 2 * constants::kWindowHeight / 5,
                                    9 * constants::kWindowWidth / 14,
                                    2 * constants::kWindowHeight / 5);
}

bool View::IsInputBlocked() const {
  return (conversation_window_ != nullptr);
}

void View::InterruptAllInput() {
  controller_->SetControlUpKeyState(false);
  controller_->SetControlRightKeyState(false);
  controller_->SetControlDownKeyState(false);
  controller_->SetControlLeftKeyState(false);
}

void View::CloseConversationWindow() {
  conversation_window_ = nullptr;
  item_bar_pack_->show();
  StartTickTimer();
}

std::pair<ItemBar*, ItemBar*> View::GetSrcDestBars(int id, int index) {
  switch (id) {
    case 0: {
      return std::make_pair(item_bar_pack_->GetHeroBar(),
                            item_bar_pack_->GetObjectBar());
    }
    case 1: {
      std::shared_ptr<Storage> storage =
          item_bar_pack_->GetItemBar(id)->GetStorage();
      if (storage->IsValidIndex(index) &&
          storage->GetItems().at(index).GetType() == Item::Type::kRoba) {
        controller_->OnItemPress(
            static_cast<int>(BarPack::BarType::kClothinBar), 0);

        return std::make_pair(item_bar_pack_->GetObjectBar(),
                              item_bar_pack_->GetClothingBar());
      }

      return std::make_pair(item_bar_pack_->GetObjectBar(),
                            item_bar_pack_->GetHeroBar());
    }
    case 2: {
      return std::make_pair(item_bar_pack_->GetClothingBar(),
                            item_bar_pack_->GetObjectBar());
    }
    default: {
      return std::make_pair(nullptr, nullptr);
    }
  }
}

bool View::IsItemDialogOpen() const {
  return is_item_dialog_open_;
}

void View::ItemDialogEvent() {
  Object* chest = controller_->FindIfNearestObject([](Object* block) {
    return block->IsStorable();
  });

  if (!is_item_dialog_open_ && chest) {
    is_item_dialog_open_ = true;
    std::shared_ptr<Storage> storage = chest->GetStorage();
    item_bar_pack_->GetObjectBar()->AssignStorage(storage);
    item_bar_pack_->GetObjectBar()->show();
  } else {
    is_item_dialog_open_ = false;
    item_bar_pack_->GetObjectBar()->hide();
  }

  item_bar_pack_->GetHeroBar()->setEnabled(is_item_dialog_open_);
  item_bar_pack_->GetObjectBar()->setEnabled(is_item_dialog_open_);
  item_bar_pack_->GetClothingBar()->setEnabled(is_item_dialog_open_);
  item_bar_pack_->GetWeaponBar()->setEnabled(is_item_dialog_open_);
}

void View::AssignHeroStorage() {
  item_bar_pack_->GetHeroBar()->AssignStorage(model_->GetHero().GetStorage());
  item_bar_pack_->GetClothingBar()->AssignStorage(model_->GetHero().GetClothingStorage());
  item_bar_pack_->GetWeaponBar()->AssignStorage(model_->GetHero().GetGunStorage());
}

void View::SetHealth(int health) {
  // health_bar_->setText(QString::number(health) + "❤");
  status_bar_->SetPrameter(StatusBar::Type::kHealth, QString::number(health));
}

void View::SetAttack(int health) {
  status_bar_->SetPrameter(StatusBar::Type::kAttack, QString::number(health));
}

BarPack* View::GetBarPack() {
  return item_bar_pack_;
}
