#include "main_menu.h"

MainMenu::MainMenu(AbstractController* controller,
                   QWidget* parent) :
                   QWidget(parent),
                   controller_(controller),
                   layout_(new QGridLayout(this)) {
  SetUi();
  SetStyles();
  show();
}

void MainMenu::SetUi() {
  QLabel* l = new QLabel("Hello", this);
  layout_->addWidget(l);

  layout_->setMargin(0);
  // layout_->setSpacing(0);
  setLayout(layout_);
}

void MainMenu::SetStyles() {
  QFile styles(":main_menu_styles");
  styles.open(QFile::ReadOnly);
  setStyleSheet(styles.readAll());
}
