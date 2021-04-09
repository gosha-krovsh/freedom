#ifndef GAMEOBJECT_OBJECT_H_
#define GAMEOBJECT_OBJECT_H_

#include <QPainter>

#include <memory>

#include "Model/constants.h"
#include "point.h"

class Object {
 public:
  explicit Object(const Point& coords,
                  const std::shared_ptr<QPixmap>& image =
                      std::shared_ptr<QPixmap>());
  virtual ~Object() = default;

  virtual void Tick(int current_time);

  void PrintInfo() const;

  Point GetCoordinates() const;
  double GetX() const;
  double GetY() const;
  double GetZ() const;
  int GetRoundedX() const;
  int GetRoundedY() const;
  int GetRoundedZ() const;
  int GetFlooredX() const;
  int GetFlooredY() const;
  void SetCoordinates(const Point& coords);
  void SetX(double x);
  void SetY(double y);
  void SetZ(double z);

  bool IsTouchable() const;

  void Draw(QPainter* painter) const;

 protected:
  bool is_touchable_{true};
  std::shared_ptr<QPixmap> image_;

 private:
  Point coordinates_;
};

#endif  // GAMEOBJECT_OBJECT_H_
