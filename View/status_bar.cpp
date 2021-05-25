#include "status_bar.h"

StatusBar::StatusBar(const std::shared_ptr<Model>& model,
                     QWidget* parent,
                     int center_x,
                     int y,
                     int width,
                     int height) :
    QWidget(parent),
    model_(model),
    layout_(new QGridLayout(this)) {
  ConfigureStatus();
  SetUi(center_x, y, width, height);
  SetStyles();
}

void StatusBar::SetUi(int center_x, int y, int width, int height) {
  SetCenterGeometry(center_x, y, width, height);
  setLayout(layout_);
  // setContentsMargins(5, 0, 0, 0);
  layout_->setMargin(0);
  layout_->setSpacing(0);

  layout_->addWidget(health_status_.first, 0, 0, 1, 1);
  layout_->addWidget(health_status_.second, 0, 1, 1, 1);
  layout_->addWidget(attack_status_.first, 1, 0, 1, 1);
  layout_->addWidget(attack_status_.second, 1, 1, 1, 1);
}

void StatusBar::SetPrameter(StatusBar::Type type, const QString& param) {
  switch (type) {
    case kHealth: {
      health_status_.second->setText(param);
      break;
    }
    case kAttack: {
      attack_status_.second->setText(param);
      break;
    }
  }
}

void StatusBar::SetCenterGeometry(int x, int y, int width, int height) {
  setGeometry(x - width / 2, y, width, height);
}

void StatusBar::ConfigureStatus() {
  QLabel* health_label = new QLabel(this);
  QLabel* helth_text_label = new QLabel(this);
  helth_text_label->setObjectName("health_bar");
  health_label->setScaledContents(true);
  health_label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  helth_text_label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  QPixmap health_pix = *model_->GetImage("heart").lock();
  health_label->setPixmap(health_pix);

  health_label->setFixedWidth(constants::kStatusBarIconSize);
  health_label->setFixedHeight(constants::kStatusBarIconSize);
  helth_text_label->setFixedHeight(constants::kStatusBarIconSize);

  health_status_ = std::make_pair(health_label, helth_text_label);

  QLabel* attack_label = new QLabel(this);
  QLabel* attack_text_label = new QLabel(this);

  attack_text_label->setObjectName("weapon_bar");
  attack_label->setScaledContents(true);
  attack_label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  attack_text_label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  QPixmap attack_pix = *model_->GetImage("knife").lock();
  attack_label->setPixmap(attack_pix);

  attack_label->setFixedWidth(constants::kStatusBarIconSize);
  attack_label->setFixedHeight(constants::kStatusBarIconSize);
  attack_text_label->setFixedHeight(constants::kStatusBarIconSize);

  attack_status_ = std::make_pair(attack_label, attack_text_label);
}

void StatusBar::SetStyles() {
  QFile styleFile(":status_bar_styles");
  styleFile.open(QFile::ReadOnly);
  QString style(styleFile.readAll());

  setStyleSheet(style);
  setObjectName("status_bar");
  setAttribute(Qt::WA_StyledBackground, true);
  styleFile.close();
}
