#include "item_bar.h"

ItemBar::ItemBar(// int x, int y, int width, int window_height,
                 int id,
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
    buttons_.emplace_back(button);
  }

  SetUi();
  SetStyles();
  ConnectButtons();

  // This bar is disabled, while you don't need to transfer items.
  // This solves the problem, that bar listeners overlap the main window ones
  setDisabled(true);
  // This bar should be shown only while playing
  // so by default it's created hidden
  hide();
}

void ItemBar::SetUi() {
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  setMouseTracking(true);

  for (auto& button : buttons_) {
    layout_->addWidget(button);
  }
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
  for (int i = 0; i < constants::kMaxElementsInItemBar; i++) {
    connect(buttons_.at(i), &QPushButton::pressed, this, [i, this]() {
      ButtonPressed(i);
    });
  }
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
  if (!storage_) {
    ClearIconsFromIndex(0);
  }

  int size = std::min(storage_->GetItems().size(),
                      static_cast<size_t>(constants::kMaxElementsInItemBar));
  for (int i = 0; i < size; i++) {
    QPixmap image = storage_->GetItems().at(i).GetImage();
    QString name = storage_->GetItems().at(i).GetName();

    QIcon icon{};
    icon.addPixmap(image, QIcon::Active);
    icon.addPixmap(image, QIcon::Disabled);
    buttons_.at(i)->setToolTip(name);
    buttons_.at(i)->setIcon(icon);
  }

  ClearIconsFromIndex(size);
}

void ItemBar::ClearIconsFromIndex(int index) {
  for (int i = index; i < constants::kMaxElementsInItemBar; i++) {
    buttons_.at(i)->setIcon(QIcon());
  }
}

void ItemBar::UseItem(int) {
  // todo::make items usable
}

void ItemBar::resizeEvent(QResizeEvent* event) {
  layout_->setSpacing(static_cast<int>(0.01 * width()));
}

void ItemBar::ResizeButtons(int width, int max_height) {
  int size = std::min(width / constants::kMaxElementsInItemBar, max_height);
  for (auto& button : buttons_) {
    button->setFixedSize(size, size);
    button->setIconSize(button->size() * 0.8);
  }
}
