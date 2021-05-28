#include "view.h"

View::View(AbstractController* controller,
           const std::shared_ptr<Model>& model) :
    controller_(controller),
    model_(model),
    timer_(new QTimer(this)),
    item_bar_pack_(new BarPack(controller, model, game_widget_.get(),
                               model_->GetHero().GetStorage(),
                               model_->GetHero().GetClothingStorage(),
                               model_->GetHero().GetGunStorage())),
    game_widget_(std::make_unique<GameWidget>(model_)),
    status_bar_(new StatusBar(model,
                              game_widget_.get(),
                              constants::kStatusBarDefaultCenteredX,
                              constants::kStatusBarDefaultY,
                              constants::kStatusBarDefaultWidth,
                              constants::kStatusBarDefaultHeight)),
    task_list_(new QuestTaskList(controller, game_widget_.get())) {}

void View::Show() {
  setMinimumSize(constants::kWindowWidth, constants::kWindowHeight);
  setWindowState(Qt::WindowFullScreen);
  SetUi();
  SetStyles();

  show();

  setCentralWidget(game_widget_.get());
  connect(timer_, &QTimer::timeout, this, &View::TimerEvent);

  game_widget_->hide();
  model_->GetSound().PlayTrack(Sound::kIntro);
  show();
  item_bar_pack_->show();
  ShowMainMenu();
}
void View::ShowGame() {
  game_widget_->show();
}
void View::HideGame() {
  game_widget_->hide();
}

void View::SetUi() {
  time_label_->setObjectName("middle_label");
  time_label_->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  time_label_->setTextInteractionFlags(
      Qt::TextInteractionFlag::NoTextInteraction);

  time_label_->setGeometry(30 * constants::kWindowWidth / 85,
                           10 * constants::kWindowHeight / 50,
                           25 * constants::kWindowWidth / 85,
                           8 * constants::kWindowHeight / 50);
  time_label_->setAlignment(Qt::AlignmentFlag::AlignCenter);

  location_label_->setObjectName("middle_label");
  location_label_->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  location_label_->setTextInteractionFlags(
      Qt::TextInteractionFlag::NoTextInteraction);

  location_label_->setGeometry(30 * constants::kWindowWidth / 85,
                               2 * constants::kWindowHeight / 50,
                               25 * constants::kWindowWidth / 85,
                               8 * constants::kWindowHeight / 50);
  location_label_->setAlignment(Qt::AlignmentFlag::AlignCenter);
}

void View::SetStyles() {
  QFile styleFile(":view_styles");
  styleFile.open(QFile::ReadOnly);
  QString style(styleFile.readAll());

  setStyleSheet(style);
  styleFile.close();
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

void View::StartConversation(
    const std::shared_ptr<Conversation>& conversation) {
  if (conversation) {
    StopTickTimer();
    conversation_window_ = new ConversationWindow(
        *conversation, controller_, this);
    InterruptAllInput();
    resizeEvent(nullptr);
    item_bar_pack_->hide();
  }
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
      StartConversation(controller_->GetNearestConversation());
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
                                    9 * constants::kWindowWidth / 14,
                                    2 * constants::kWindowHeight / 5);
  time_label_->setGeometry(35 * width() / 85,
                           6 * height() / 50,
                           15 * width() / 85,
                           4 * constants::kWindowHeight / 50);
  location_label_->setGeometry(30 * width() / 85,
                           2 * height() / 50,
                           25 * width() / 85,
                           4 * constants::kWindowHeight / 50);
  task_list_->setGeometry(
      constants::kXQuestTaskListWindowMultiplier * width(),
      constants::kYQuestTaskListWindowMultiplier * height(),
      constants::kWidthQuestTaskListWindowMultiplier * width(),
      constants::kHeightQuestTaskListWindowMultiplier * height());
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
  conversation_window_->deleteLater();
  conversation_window_ = nullptr;
  item_bar_pack_->show();
  StartTickTimer();
}

void View::CloseMainMenu() {
  main_menu_->deleteLater();
  main_menu_ = nullptr;
  status_bar_->show();
  time_label_->show();
  location_label_->show();
  item_bar_pack_->show();

  StartTickTimer();
  model_->GetSound().ResumeAllTracks();
}

std::pair<ItemBar*, ItemBar*> View::GetSrcDestBars(int id, int index) {
  switch (id) {
    case 0: {
      return std::make_pair(item_bar_pack_->GetHeroBar(),
                            item_bar_pack_->GetObjectBar());
    }
    case 1: {
      auto storage = item_bar_pack_->GetItemBar(id)->GetStorage();
      if (storage->IsValidIndex(index)) {
        auto item_type = storage->GetItems().at(index).GetType();
        if (item_type == Item::Type::kPrisonerRoba ||
            item_type == Item::Type::kPoliceRoba) {
          controller_->OnItemPress(
              static_cast<int>(BarPack::BarType::kClothinBar), 0);

          return std::make_pair(item_bar_pack_->GetObjectBar(),
                                item_bar_pack_->GetClothingBar());
        }
        if (item_type == Item::Type::kKnife) {
          controller_->OnItemPress(
              static_cast<int>(BarPack::BarType::kWeaponBar), 0);

          return std::make_pair(item_bar_pack_->GetObjectBar(),
                                item_bar_pack_->GetWeaponBar());
        }
      }
      return std::make_pair(item_bar_pack_->GetObjectBar(),
                            item_bar_pack_->GetHeroBar());
    }
    case 2: {
      return std::make_pair(item_bar_pack_->GetClothingBar(),
                            item_bar_pack_->GetObjectBar());
    }
    case 3 : {
      return std::make_pair(item_bar_pack_->GetWeaponBar(),
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
  auto storage = controller_->GetInteractableStorage();
  if (!is_item_dialog_open_ && storage) {
    is_item_dialog_open_ = true;
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
  item_bar_pack_->GetHeroBar()->AssignStorage(
      model_->GetHero().GetStorage());
  item_bar_pack_->GetClothingBar()->AssignStorage(
      model_->GetHero().GetClothingStorage());
  item_bar_pack_->GetWeaponBar()->AssignStorage(
      model_->GetHero().GetGunStorage());
}

void View::SetHealth(int health) {
  status_bar_->SetPrameter(StatusBar::Type::kHealth, QString::number(health));
}

void View::SetAttack(int attack) {
  status_bar_->SetPrameter(StatusBar::Type::kAttack, QString::number(attack));
}

BarPack* View::GetBarPack() {
  return item_bar_pack_;
}

QuestTaskList* View::GetQuestTaskList() {
  return task_list_;
}

void View::SetTime(const Time& time) {
  time_label_->setText(QString::fromStdString(time.ToString()));
}

void View::SetLocation(const QString& location_str) {
  location_label_->setText(location_str);
}

void View::ShowMainMenu() {
  main_menu_ = new MainMenu(controller_, this);
  item_bar_pack_->hide();
  status_bar_->hide();
  time_label_->hide();
  location_label_->hide();

  InterruptAllInput();
  resizeEvent(nullptr);
  model_->GetSound().PauseAllTracks();
}

void View::AddQuestToTaskList(const QString& quest_name,
                              const std::vector<QString>& node_strings) {
    task_list_->SetQuestString(quest_name, node_strings);
    task_list_->UpdateCurrentLables(quest_name, 0);
}

void View::UpdateQuestTaskList(const QString& quest_name, int index) {
    task_list_->UpdateCurrentLables(quest_name, index);
}

void View::UpdateStatusBar() {
  SetHealth(model_->GetHero().GetHP());
  SetAttack(model_->GetHero().GetAttack());
  SetTime(model_->GetTime());
  SetLocation(model_->GetMap().GetCurrentRoom().name);
}
