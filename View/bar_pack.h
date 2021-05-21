#ifndef VIEW_BAR_PACK_H_
#define VIEW_BAR_PACK_H_

#include <QGridLayout>
#include <memory>

#include "item_bar.h"
#include "Model/model.h"

class BarPack : public QWidget {
  Q_OBJECT

 public:
  BarPack(AbstractController* controller,
          const std::shared_ptr<Model>& model,
          QWidget* parent = nullptr,
          const std::shared_ptr<Storage>& hero_storage = nullptr,
          const std::shared_ptr<Storage>& object_storage = nullptr,
          const std::shared_ptr<Storage>& hero_clothing_storage = nullptr,
          const std::shared_ptr<Storage>& hero_gun_storage = nullptr,
          int center_x = constants::kBarPackDefaultCenteredX,
          int y = constants::kBarPackDefaultY,
          int width = constants::kBarPackDefaultWidth,
          int height = constants::kBarPackDefaultHeight);

  ItemBar* GetHeroBar();
  ItemBar* GetObjectBar();

  void SetCenterGeometry(int x, int y, int width, int height);

 private:
  void SetUi(int center_x, int y, int width, int height);

  std::shared_ptr<Model> model_;

  ItemBar* clothing_bar_;
  ItemBar* gun_bar_;
  ItemBar* hero_bar_;
  ItemBar* object_bar_;
  QGridLayout* layout_;
};

#endif  // VIEW_BAR_PACK_H_
