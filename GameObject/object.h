#ifndef GAMEOBJECT_OBJECT_H_
#define GAMEOBJECT_OBJECT_H_

#include <QPainter>

#include "Model/constants.h"
#include "coordinates.h"

class Object {
 public:
  Object(const Coordinates& coords, const QPixmap& image);
  virtual ~Object() = default;

  virtual void Tick(int current_time);

  Coordinates GetCoordinates() const;
  double GetX() const;
  double GetY() const;
  double GetZ() const;
  void SetCoordinates(Coordinates coords);

  bool IsTouchable() const;

  void Draw(QPainter* painter) const;

 protected:
  bool is_touchable_{ true };

 private:
  Coordinates coordinates_;
  QPixmap image_;
};

#endif  // GAMEOBJECT_OBJECT_H_
