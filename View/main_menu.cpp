#include "main_menu.h"

MainMenu::MainMenu(AbstractController* controller,
                   QWidget* parent) :
                   QWidget(parent),
                   controller_(controller),
                   layout_(new QGridLayout(this)),
                   play_button_(new QPushButton("Играть", this)),
                   settings_button_(new QPushButton("Настройки", this)),
                   exit_button_(new QPushButton("Выход", this)),
                   settings_menu_(new SettingsMenu(controller_, this)) {
  SetUi();
  SetStyles();
  ConnectButtons();
  show();
}

void MainMenu::SetUi() {
  play_button_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  settings_button_->setSizePolicy(QSizePolicy::Expanding,
                                  QSizePolicy::Expanding);
  exit_button_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  settings_menu_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  layout_->addWidget(play_button_, 1, 2);
  layout_->addWidget(settings_button_, 3, 2);
  layout_->addWidget(exit_button_, 5, 2);
  layout_->addWidget(settings_menu_, 1, 1, 5, 1);

  // Adjust horizontal margins for buttons
  layout_->setColumnStretch(0, 1);
  layout_->setColumnStretch(1, 18);  // settings_menu
  layout_->setColumnStretch(2, 6);  // all buttons here
  layout_->setColumnStretch(3, 1);

  // Adjust vertical margins for buttons
  layout_->setRowStretch(0, 2);
  layout_->setRowStretch(1, 1);  // play_button
  layout_->setRowStretch(2, 2);
  layout_->setRowStretch(3, 1);  // settings_button_
  layout_->setRowStretch(4, 2);
  layout_->setRowStretch(5, 1);  // exit_button_
  layout_->setRowStretch(6, 2);

  layout_->setMargin(0);
  setLayout(layout_);
}

void MainMenu::SetStyles() {
  QFile styles(":main_menu_styles");
  styles.open(QFile::ReadOnly);
  setObjectName("main_menu");
  setStyleSheet(styles.readAll());
}

void MainMenu::ConnectButtons() {
  connect(play_button_, &QPushButton::pressed, this, [this]() {
    controller_->CloseMainMenu();
    controller_->PlayTrackOnce(Sound::kButtonClick);
  });
  connect(exit_button_, &QPushButton::pressed,
          QApplication::instance(), &QCoreApplication::quit);
  connect(settings_button_, &QPushButton::pressed, this, [this]() {
    settings_menu_->show();
    controller_->PlayTrackOnce(Sound::kButtonClick);
  });
}

void MainMenu::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  painter.drawPixmap(0, 0, width(), height(), background_image_);
}
