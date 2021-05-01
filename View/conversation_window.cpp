#include "conversation_window.h"

ConversationWindow::ConversationWindow(
    AbstractController* controller, QWidget* parent) : QWidget(parent),
    controller_(controller),
    scroll_area_(new QScrollArea(this)),
    content_(new QWidget(this)),
    layout_(new QGridLayout(this)) {
  hide();
  SetStyles();
  SetUi();
}

void ConversationWindow::SetUi() {
  for (int i = 0; i < 10; ++i) {
    layout_->addWidget(new QLabel("text", this), i, (i % 2 == 0) ? 0 : 1);
  }
  content_->setLayout(layout_);
  content_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  scroll_area_->setWidget(content_);
  scroll_area_->setAlignment(Qt::AlignCenter);
}

void ConversationWindow::SetStyles() {
  QFile styles(":conversation_window_styles");
  styles.open(QFile::ReadOnly);
  setStyleSheet(styles.readAll());
}

void ConversationWindow::resizeEvent(QResizeEvent*) {
  scroll_area_->setGeometry(0, 0, width(), height());
  content_->setGeometry(0.1 * width(), content_->y(),
                        0.8 * width(), content_->height());
}
