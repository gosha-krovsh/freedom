#include "view.h"

View::View(AbstractController* controller,
           const std::shared_ptr<Model>& model) :
    controller_(controller),
    model_(model),
    timer_(new QTimer(this)),
    item_bar_pack_(new BarPack(controller, this,
                               model_->GetHero().GetStorage())),
    game_widget_(std::make_unique<GameWidget>(model_)) {}

void View::Show() {
  setMinimumSize(constants::kWindowWidth, constants::kWindowHeight);
  setWindowState(Qt::WindowFullScreen);

  setCentralWidget(game_widget_.get());
  connect(timer_, &QTimer::timeout, this, &View::TimerEvent);

  show();
  item_bar_pack_->show();
  ShowMainMenu();
}

void View::StartTickTimer() {
  timer_->start(1000 / Settings::kFPS);
}

void View::StopTickTimer() {
  timer_->stop();
}

void View::TimerEvent() {
  controller_->Tick();
  game_widget_->repaint();
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
    case Qt::Key_R: {
      controller_->InteractWithDoor();
      break;
    }
    case Qt::Key_Escape: {
      StopTickTimer();
      ShowMainMenu();
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
  if (main_menu_) {
    main_menu_->setGeometry(0, 0, width(), height());
  }
  item_bar_pack_->SetCenterGeometry(width() / 2,
                                    height() - 2 * constants::kWindowHeight / 5,
                                    constants::kWindowWidth / 2,
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

void View::CloseMainMenu() {
  main_menu_ = nullptr;
  StartTickTimer();
}

std::pair<ItemBar*, ItemBar*> View::GetSrcDestBars(int id) {
  switch (id) {
    case 0: {
      return std::make_pair(item_bar_pack_->GetHeroBar(),
                            item_bar_pack_->GetObjectBar());
    }
    case 1: {
      return std::make_pair(item_bar_pack_->GetObjectBar(),
                            item_bar_pack_->GetHeroBar());
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
}

void View::AssignHeroStorage() {
  item_bar_pack_->GetHeroBar()->AssignStorage(model_->GetHero().GetStorage());
}

void View::ShowMainMenu() {
  main_menu_ = std::make_unique<MainMenu>(controller_, this);
  InterruptAllInput();
  resizeEvent(nullptr);
}
