#include "status_bar.h"

StatusBar::StatusBar(const std::shared_ptr<Model>& model,
                     const std::set<Type>& generate_fields,
                     QWidget* parent,
                     int center_x,
                     int y,
                     int width,
                     int height) :
    QWidget(parent),
    model_(model),
    layout_(new QGridLayout(this)) {
  ConfigureStatus(generate_fields);
  SetUi(center_x, y, width, height);
  SetStyles();
}

void StatusBar::SetUi(int center_x, int y, int width, int height) {
  SetCenterGeometry(center_x, y, width, height);
  setLayout(layout_);
  setContentsMargins(0, 0, 0, 0);

  int row = 0;
  for (auto& label_pair : status_) {
    layout_->addWidget(label_pair.second.first, row, 0, 1, 1);
    layout_->addWidget(label_pair.second.second, row, 1, 1, 1);
    ++row;
  }
}

void StatusBar::SetPrameter(StatusBar::Type type, const QString& param) {
  status_[type].second->setText(param);
}

void StatusBar::SetCenterGeometry(int x, int y, int width, int height) {
  setGeometry(x - width / 2, y, width, height);
}

void StatusBar::ConfigureStatus(const std::set<Type>& generate_fields) {
  for (const auto& type : generate_fields) {
    switch (type) {
      case kHealth: {
        QLabel* label = new QLabel(this);
        QLabel* text_label = new QLabel(this);
        text_label->setObjectName("health_bar");
        label->setScaledContents(true);
        label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        text_label->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

        QPixmap health_pix = *model_->GetImage("heart").lock();
        label->setPixmap(health_pix);

        label->setFixedWidth(constants::kStatusBarIconSize);
        label->setFixedHeight(constants::kStatusBarIconSize);
        text_label->setFixedHeight(constants::kStatusBarIconSize);

        status_.insert(std::make_pair(kHealth,
                                      std::make_pair(label, text_label)));
        break;
      }
      case kAttack: {
        QLabel* label = new QLabel(this);
        QLabel* text_label = new QLabel(this);
        text_label->setObjectName("weapon_bar");
        label->setScaledContents(true);
        label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        text_label->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

        QPixmap attack_pix = *model_->GetImage("ak_47").lock();
        label->setPixmap(attack_pix);

        label->setFixedWidth(constants::kStatusBarIconSize);
        label->setFixedHeight(constants::kStatusBarIconSize);
        text_label->setFixedHeight(constants::kStatusBarIconSize);
        text_label->setFixedWidth(constants::kStatusBarIconSize);

        status_.insert(std::make_pair(kAttack,
                                      std::make_pair(label, text_label)));
        break;
      }
    }
  }
}

void StatusBar::SetStyles() {
  QFile styleFile(":status_bar_styles");
  styleFile.open(QFile::ReadOnly);
  QString style(styleFile.readAll());

  setStyleSheet(style);
  styleFile.close();
}
