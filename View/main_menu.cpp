#include "main_menu.h"

MainMenu::MainMenu(AbstractController* controller,
                   QWidget* parent) :
                   QWidget(parent),
                   controller_(controller),
                   layout_(new QGridLayout(this)),
                   play_button_(new QPushButton("Play", this)),
                   settings_button_(new QPushButton("Settings", this)),
                   exit_button_(new QPushButton("Exit", this)) {
  SetUi();
  SetStyles();
  show();
}

void MainMenu::SetUi() {
  layout_->addWidget(play_button_);
  layout_->addWidget(settings_button_);
  layout_->addWidget(exit_button_);

  layout_->setMargin(0);
  // layout_->setSpacing(0);
  setLayout(layout_);
}

void MainMenu::SetStyles() {
  QFile styles(":main_menu_styles");
  styles.open(QFile::ReadOnly);
  setObjectName("main_menu");
  setStyleSheet(styles.readAll());
}

void MainMenu::paintEvent(QPaintEvent*) {
  QStyleOption opt;
  opt.init(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
