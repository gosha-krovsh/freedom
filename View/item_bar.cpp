#include "item_bar.h"

ItemBar::ItemBar(int x, int y, int width, int height, int id,
                 AbstractController* controller,
                 QWidget* parent,
                 StorableObject* storage,
                 Qt::WindowFlags f) : QWidget(parent, f),
                                      id_(id),
                                      controller_(controller),
                                      storage_(storage),
                                      layout_(new QHBoxLayout()) {
  for (int i = 0; i < constants::kMaxElementsInItemBar; i++) {
    QPushButton* button = new QPushButton(this);
    button->setObjectName(tr("item_bar_button"));
    button->setMinimumSize(width / constants::kMaxElementsInItemBar,
                           std::min(height,
                                    width / constants::kMaxElementsInItemBar));

    buttons_.emplace_back(button);
  }

  SetUi(x, y, width, height);
  ConnectButtons();

  // This bar is disabled, while you don't need to transfer items.
  // This solves the problem, that bar listeners overlap the main window ones
  setDisabled(true);
  // This bar should be shown only while playing
  // so by default it's created hidden
  hide();
}

void ItemBar::SetUi(int x, int y, int width, int height) {
  setGeometry(x, y, width, height);
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  setMouseTracking(true);

  for (auto& button : buttons_) {
    layout_->addWidget(button);
  }
  setLayout(layout_);
}

void ItemBar::ConnectButtons() {
  for (int i = 0; i < constants::kMaxElementsInItemBar; i++) {
    connect(buttons_.at(i), &QPushButton::pressed, this, [i, this]() {
      ButtonPressed(i);
    });
  }
}

void ItemBar::Show() {
  show();
}

void ItemBar::Hide() {
  hide();
}

void ItemBar::SetEnabled(bool flag) {
  setEnabled(flag);
}

void ItemBar::AssignObject(StorableObject* object) {
  storage_ = object;
  UpdateIcons();
}

void ItemBar::ButtonPressed(int index) {
  controller_->OnItemPress(id_, index);
}

int ItemBar::GetId() const {
  return id_;
}

StorableObject* ItemBar::GetObject() const {
  return storage_;
}

void ItemBar::UpdateIcons() {
  if (storage_) {
    size_t size = std::min(storage_->GetItems().size(),
                  static_cast<size_t>(constants::kMaxElementsInItemBar));
    for (size_t i = 0; i < size; i++) {
      QPixmap image = storage_->GetItems().at(i).GetImage();
      QString name =
          QString::fromStdString(storage_->GetItems().at(i).GetName());

      QIcon icon = QIcon();
      icon.addPixmap(image, QIcon::Active);
      icon.addPixmap(image, QIcon::Disabled);
      buttons_.at(i)->setToolTip(name);
      buttons_.at(i)->setIcon(icon);
      buttons_.at(i)->setIconSize(buttons_.at(i)->size() * 0.8);
    }

    ClearIconsFromIndex(size);
  } else {
    ClearIconsFromIndex(0);
  }
}

void ItemBar::ClearIconsFromIndex(size_t index) {
  for (size_t i = index; i < constants::kMaxElementsInItemBar; i++) {
    buttons_.at(i)->setIcon(QIcon());
  }
}

void ItemBar::UseItem(int) {
  // todo::make items usable
}
