#ifndef VIEW_BAR_PACK_H_
#define VIEW_BAR_PACK_H_

#include <QVBoxLayout>
#include <memory>

#include "item_bar.h"

class BarPack : public QWidget {
  Q_OBJECT

 public:
  BarPack(AbstractController* controller,
          QWidget* parent = nullptr,
          const std::shared_ptr<Storage>& hero_storage = nullptr,
          const std::shared_ptr<Storage>& object_storage = nullptr,
          int center_x = constants::kWindowWidth / 2,
          int y = 3 * constants::kWindowHeight / 5,
          int width = constants::kWindowWidth / 2,
          int height = 2 * constants::kWindowHeight / 5);

  ItemBar* GetHeroBar();
  ItemBar* GetObjectBar();

  void SetCenterGeometry(int x, int y, int width, int height);

 private:
  void SetUi(int center_x, int y, int width, int height);

  ItemBar* hero_bar_;
  ItemBar* object_bar_;
  QVBoxLayout* layout_;
};

#endif  // VIEW_BAR_PACK_H_
