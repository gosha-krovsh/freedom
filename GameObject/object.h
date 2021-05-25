#ifndef GAMEOBJECT_OBJECT_H_
#define GAMEOBJECT_OBJECT_H_

#include <QPainter>

#include <memory>

#include "Model/constants.h"
#include "Model/settings.h"
#include "point.h"
#include "interacting_object.h"
#include "storage.h"

class Object {
 public:
  enum class Type {
    kNone = 0,
    kFloor = 1,
    kWall = 2,
    kChest = 3,
    kBasketRing225 = 4,
    kBasketRing315 = 5,
    kFence225 = 6,
    kFence315 = 7,
    kGrass = 8,
    kBasketballFloorWithLine45 = 9,
    kBasketballFloorWithLine135 = 10,
    kBasketballFloorWithLine225 = 11,
    kBasketballFloorWithLine315 = 12,
    kBasketballFloor = 13,
    kTable = 14,
    kChair = 15,
    kStoneRoad = 16,
    kMud = 17,
    kBall = 18,
    kBed_45 = 19,
    kBed_135 = 20,
    kBed_225 = 21,
    kBed_315 = 22,
    kWardrobe_45 = 23,
    kWardrobe_225 = 24,
    kWardrobe_315 = 25,
    kGrating_225 = 26,
    kGrating_315 = 27,
    kDoor_225 = 28,
    kDoor_315 = 29,
  };

 public:
  explicit Object(const Point& coords,
                  const std::weak_ptr<QPixmap>& image =
                      std::weak_ptr<QPixmap>(),
                  Type type = Type::kNone);
  virtual ~Object() = default;

  virtual void Tick(int current_time);



  virtual Point GetDrawOffset() const;
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

  std::shared_ptr<Storage> GetStorage();

  bool IsTouchable() const;
  bool IsStorable() const;
  bool IsType(Type object_type) const;
  bool ToDelete() const;

  void Draw(QPainter* painter) const;
  virtual void Interact(const InteractingObject& interacting_object);

 protected:
  std::weak_ptr<QPixmap> image_;
  bool is_touchable_{true};
  bool delete_on_next_tick_{false};
  Type type_{Type::kNone};

  std::shared_ptr<Storage> storage_ = nullptr;

 private:
  Point coordinates_;
};

#endif  // GAMEOBJECT_OBJECT_H_
