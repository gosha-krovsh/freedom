#include "bar_pack.h"

BarPack::BarPack(AbstractController* controller,
                 const std::shared_ptr<Model>& model,
                 QWidget* parent,
                 const std::shared_ptr<Storage>& hero_storage,
                 const std::shared_ptr<Storage>& object_storage,
                 const std::shared_ptr<Storage>& hero_clothing_storage,
                 const std::shared_ptr<Storage>& hero_gun_storage,
                 int center_x, int y, int width, int height) :
    QWidget(parent),
    model_(model),
    layout_(new QGridLayout(this)),
    hero_bar_(new ItemBar(0,
                          constants::kMaxElementsInItemBar,
                          controller,
                          this,
                          hero_storage)),
    object_bar_(new ItemBar(1,
                            constants::kMaxElementsInItemBar,
                            controller,
                            this,
                            object_storage)),
    clothing_bar_(new ItemBar(1,
                              1,
                              controller,
                              this,
                              hero_clothing_storage,
                              model->GetImage("brick").lock())),
    gun_bar_(new ItemBar(1,
                         1,
                         controller,
                         this,
                         hero_gun_storage)) {
  SetUi(center_x, y, width, height);
  hero_bar_->show();
  clothing_bar_->show();
  gun_bar_->show();
}

void BarPack::SetUi(int center_x, int y, int width, int height) {
  SetCenterGeometry(center_x, y, width, height);

  // This code keeps child widgets on their place, when you hide others.
  QSizePolicy retain = object_bar_->sizePolicy();
  retain.setRetainSizeWhenHidden(true);
  object_bar_->setSizePolicy(retain);

  int real_width = width / (constants::kMaxElementsInItemBar + 2);
  clothing_bar_->SetButtonsSize(real_width * 1.1, height / 2);
  gun_bar_->SetButtonsSize(real_width * 1.1, height / 2);
  hero_bar_->SetButtonsSize(real_width * constants::kMaxElementsInItemBar,
                            height / 2);
  object_bar_->SetButtonsSize(real_width * constants::kMaxElementsInItemBar,
                              height / 2);

  layout_->addWidget(clothing_bar_, 1, 0,1, 1);
  layout_->addWidget(hero_bar_, 1, 1, 1, 1);
  layout_->addWidget(object_bar_, 0, 1, 1, 1);
  layout_->addWidget(gun_bar_, 1, 2, 1, 1);

  layout_->setSpacing(0);
  layout_->setContentsMargins(0,0,0,0);

  setLayout(layout_);
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
