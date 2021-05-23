#include "settings_menu.h"

SettingsMenu::SettingsMenu(AbstractController* controller,
                   QWidget* parent) :
                   QWidget(parent),
                   controller_(controller),
                   layout_(new QGridLayout(this)),
                   volume_slider_(
                       new QSlider(Qt::Orientation::Horizontal, this)),
                   fps_combo_box_(new QComboBox(this)),
                   zoom_edit_(new QLineEdit(this)),
                   submit_button_(new QPushButton("Применить", this)),
                   back_button_(new QPushButton("Назад", this)) {
  SetUi();
  SetStyles();
  ConnectButtons();
  hide();
}

void SettingsMenu::SetUi() {
  volume_slider_->setTickInterval(100);
  volume_slider_->setSingleStep(1);
  layout_->addWidget(new QLabel("Громкость", this), 1, 1, 1, 2);
  layout_->addWidget(volume_slider_, 1, 3, 1, 2);

  fps_combo_box_->addItem(QString::number(30));
  fps_combo_box_->addItem(QString::number(60));
  layout_->addWidget(new QLabel("Количество кадров в секунду", this),
                     3, 1, 1, 2);
  layout_->addWidget(fps_combo_box_, 3, 3, 1, 2);

  layout_->addWidget(new QLabel("Приближение", this), 5, 1, 1, 2);
  layout_->addWidget(zoom_edit_, 5, 3, 1, 2);

  layout_->addWidget(submit_button_, 7, 3);
  layout_->addWidget(back_button_, 7, 4);

  // Adjust horizontal margins for buttons
  layout_->setColumnStretch(0, 1);
  layout_->setColumnStretch(1, 6);
  layout_->setColumnStretch(2, 6);
  layout_->setColumnStretch(3, 6);
  layout_->setColumnStretch(4, 6);
  layout_->setColumnStretch(5, 1);

  // Adjust vertical margins for buttons
  layout_->setRowStretch(0, 2);
  layout_->setRowStretch(1, 1);  // volume_slider_
  layout_->setRowStretch(2, 2);
  layout_->setRowStretch(3, 1);  // fps_combo_box_
  layout_->setRowStretch(4, 2);
  layout_->setRowStretch(5, 1);  // zoom_edit_
  layout_->setRowStretch(6, 2);
  layout_->setRowStretch(7, 1);  // submit_button_ & back_button_
  layout_->setRowStretch(8, 2);

  layout_->setMargin(0);
  setLayout(layout_);
}

void SettingsMenu::SetStyles() {
  QFile styles(":settings_menu_styles");
  styles.open(QFile::ReadOnly);
  setObjectName("settings_menu");
  setStyleSheet(styles.readAll());
}

void SettingsMenu::paintEvent(QPaintEvent*) {
  QStyleOption option;
  option.init(this);
  QPainter painter(this);
  style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}

void SettingsMenu::ConnectButtons() {
  connect(back_button_, &QPushButton::pressed, this, &QWidget::hide);
  connect(submit_button_, &QPushButton::pressed, this, [this]() {
    SaveData();
    controller_->UpdateVolume();
    hide();
  });
}

void SettingsMenu::SaveData() {
  Settings::kVolume = volume_slider_->value();
  Settings::kFPS = fps_combo_box_->currentText().toInt();

  bool is_zoom_value_conversion_valid;
  int zoom_value = zoom_edit_->text().toInt(&is_zoom_value_conversion_valid);
  if (is_zoom_value_conversion_valid) {
    Settings::kBlockSize = zoom_value;
  }
}

void SettingsMenu::UpdateContent() {
  volume_slider_->setValue(Settings::kVolume);
  fps_combo_box_->setCurrentText(QString::number(Settings::kFPS));
  zoom_edit_->setText(QString::number(Settings::kBlockSize));
}

void SettingsMenu::showEvent(QShowEvent* ev) {
  UpdateContent();
}
