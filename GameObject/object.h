#ifndef GAMEOBJECT_OBJECT_H_
#define GAMEOBJECT_OBJECT_H_

#include <QPainter>

#include "Model/constants.h"
#include "point.h"

class Object {
 public:
  Object(const Point& coords, const QPixmap& image);
  virtual ~Object() = default;

  virtual void Tick(int current_time);

  Point GetCoordinates() const;
  double GetX() const;
  double GetY() const;
  double GetZ() const;
  void SetCoordinates(Point coords);

  bool IsTouchable() const;

  void Draw(QPainter* painter) const;

 protected:
  bool is_touchable_{ true };

 private:
  Point coordinates_;
  QPixmap image_;
};

#endif  // GAMEOBJECT_OBJECT_H_
