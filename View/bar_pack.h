#ifndef VIEW_BAR_PACK_H_
#define VIEW_BAR_PACK_H_

#include <QVBoxLayout>
#include <memory>

#include "item_bar.h"

class BarPack : public QWidget {
  Q_OBJECT

 public:
  BarPack(int center_x, int y, int width, int height,
          AbstractController* controller,
          QWidget* parent = nullptr,
          const std::shared_ptr<Storage>& hero_storage = nullptr,
          const std::shared_ptr<Storage>& object_storage = nullptr);

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
