#ifndef VIEW_BAR_PACK_H
#define VIEW_BAR_PACK_H

#include <QVBoxLayout>

#include "item_bar.h"

class BarPack : public QWidget {
  Q_OBJECT

 public:
  BarPack(int center_x, int y, int width, int height,
          AbstractController* controller,
          QWidget* parent = nullptr,
          StorableObject* hero_storage = nullptr,
          StorableObject* object_storage = nullptr,
          Qt::WindowFlags f = Qt::WindowFlags());

  ItemBar* GetHeroBar();
  ItemBar* GetObjectBar();

  void SetCenterGeometry(int x, int y, int width, int height);

 private:
  void SetUi(int center_x, int y, int width, int height);

  ItemBar* hero_bar_;
  ItemBar* object_bar_;
  QVBoxLayout* layout_;
};

#endif // VIEW_BAR_PACK_H
