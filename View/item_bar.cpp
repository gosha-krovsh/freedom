#include "item_bar.h"

ItemBar::ItemBar(int id,
                 int size,
                 AbstractController* controller,
                 QWidget* parent,
                 const std::shared_ptr<Storage>& storage,
                 const std::shared_ptr<QPixmap>& no_item_image)
                 : QWidget(parent),
                   id_(id),
                   size_(size),
                   controller_(controller),
                   storage_(storage),
                   no_item_image_(no_item_image),
                   layout_(new QHBoxLayout()) {
  for (int i = 0; i < size_; ++i) {
    QPushButton* button = new QPushButton(this);
    button->setObjectName(tr("item_bar_button"));
    // NoFocus policy doesn't allow buttons to overlap arrow-keys functionality
    button->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    buttons_.emplace_back(button);
  }

  SetUi();
  SetStyles();
  ConnectButtons();
  UpdateIcons();
  // This bar is disabled, while you don't need to transfer items.
  // This solves the problem, that bar listeners overlap the main window ones
  setDisabled(true);
  // This bar should be shown only while playing
  // so by default it's created hidden
  hide();
}

void ItemBar::SetUi() {
  setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  setMouseTracking(true);

  for (auto& button : buttons_) {
    layout_->addWidget(button);
  }

  layout_->setContentsMargins(0, 0, 0, 0);
  layout_->setSpacing(0);
  setLayout(layout_);
}

void ItemBar::SetStyles() {
  QFile styleFile(":item_bar_styles");
  styleFile.open(QFile::ReadOnly);
  QString style(styleFile.readAll());

  setStyleSheet(style);
  styleFile.close();
}

void ItemBar::ConnectButtons() {
  for (int i = 0; i < size_; ++i) {
    connect(buttons_.at(i), &QPushButton::pressed, this, [i, this]() {
      ButtonPressed(i);
    });
  }
}

void ItemBar::AssignStorage(const std::shared_ptr<Storage>& object) {
  storage_ = object;
  UpdateIcons();
}

void ItemBar::ButtonPressed(int index) {
  controller_->OnItemPress(id_, index);
}

int ItemBar::GetId() const {
  return id_;
}

std::shared_ptr<Storage> ItemBar::GetStorage() const {
  return storage_;
}

void ItemBar::UpdateIcons() {
  if (!storage_) {
    ClearIconsFromIndex(0);
    return;
  }

  int size = std::min(static_cast<int>(storage_->GetItems().size()),
                      size_);
  for (int i = 0; i < size; ++i) {
    std::weak_ptr<QPixmap> image = storage_->GetItems().at(i).GetImage();
    QString name = storage_->GetItems().at(i).GetName();

    QIcon icon;
    icon.addPixmap(*image.lock(), QIcon::Active);
    icon.addPixmap(*image.lock(), QIcon::Disabled);
    buttons_.at(i)->setToolTip(name);
    buttons_.at(i)->setIcon(icon);
  }

  ClearIconsFromIndex(size);
}

void ItemBar::ClearIconsFromIndex(int index) {
  for (int i = index; i < size_; ++i) {
    if (no_item_image_ == nullptr) {
      buttons_.at(i)->setIcon(QIcon());
      continue;
    }

    QIcon icon;
    icon.addPixmap(*no_item_image_, QIcon::Disabled);
    buttons_.at(i)->setIcon(icon);
  }
}

void ItemBar::UseItem(int index) {
  if (!storage_->IsValidIndex(index)) {
    return;
  } else if (!storage_->GetItems().at(index).IsUsable()) {
    return;
  }

  controller_->UseItem(storage_->GetItems().at(index));
  storage_->RemoveItem(index);
  UpdateIcons();
}

void ItemBar::resizeEvent(QResizeEvent* event) {
  layout_->setSpacing(width() / 100);
}

void ItemBar::SetButtonsSize(int width, int max_height) {
  int size = std::min(width / size_, max_height);
  int space_between_buttons =
      size / constants::kCoeffitientForSpaceBetweenButtons;

  size -= space_between_buttons;
  for (auto& button : buttons_) {
    button->setFixedSize(size, size);
    button->setIconSize(button->size() * constants::kCoeffitientForIconSize);
  }
}
