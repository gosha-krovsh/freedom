#include "bar_pack.h"
BarPack::BarPack(int center_x, int y, int width, int height,
                 AbstractController* controller,
                 QWidget* parent,
                 const std::shared_ptr<Storage>& hero_storage,
                 const std::shared_ptr<Storage>& object_storage,
                 Qt::WindowFlags f) :
    QWidget(parent, f),
    layout_(new QVBoxLayout(this)),
    hero_bar_(new ItemBar(0, controller, this, hero_storage)),
    object_bar_(new ItemBar(1, controller, this, object_storage)) {
  SetUi(center_x, y, width, height);
  hero_bar_->show();
}

void BarPack::SetUi(int center_x, int y, int width, int height) {
  SetCenterGeometry(center_x, y, width, height);

  // This code keeps child widgets on their place, when you hide others.
  QSizePolicy retain = object_bar_->sizePolicy();
  retain.setRetainSizeWhenHidden(true);
  object_bar_->setSizePolicy(retain);

  layout_->addWidget(object_bar_);
  layout_->addWidget(hero_bar_);
  setLayout(layout_);

  hero_bar_->ResizeButtons(width, height / 2);
  object_bar_->ResizeButtons(width, height / 2);
}

ItemBar* BarPack::GetHeroBar() {
  return hero_bar_;
}

ItemBar* BarPack::GetObjectBar() {
  return object_bar_;
}

void BarPack::SetCenterGeometry(int x, int y, int width, int height) {
  setGeometry(x - width / 2, y, width, height);
}
