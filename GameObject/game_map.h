#ifndef GAMEOBJECT_GAME_MAP_H_
#define GAMEOBJECT_GAME_MAP_H_

#include <QDebug>

#include <vector>
#include <unordered_set>
#include <set>

#include "object.h"

class GameMap {
 public:
  struct Room {
    Room(const QString& name,
         int bottom_left_x, int bottom_left_y,
         int up_right_x, int up_right_y);

    bool IsInside(int x, int y) const;
    bool IsInsideOrOnTheEdge(int x, int y) const;
    bool IsOnTheEdge(int x, int y) const;

    bool operator==(const Room& rhs) const;
    bool operator!=(const Room& rhs) const;

    QString name;
    int bottom_left_x;
    int bottom_left_y;
    int up_right_x;
    int up_right_y;
  };

 public:
  GameMap() = default;
  GameMap(int x_size, int y_size, int z_size,
          const std::vector<Object*>& objects,
          const std::vector<Room>& rooms,
          int hero_z = 1);
  ~GameMap();

  int GetXSize() const;
  int GetYSize() const;
  int GetZSize() const;
  const Object* GetBlock(int x, int y, int z) const;

  // Updates |current_room_| by hero coordinates. If hero is on the edge of the
  // room (usually it means in the doorway), we assume that he wants to go to
  // another room and that's why also update room in this case. This also makes
  // wall transparency effect prettier.
  void UpdateCurrentRoom(int hero_x, int hero_y);
  std::unordered_set<const Object*> GetTransparentBlocks() const;

 private:
  // Returns all blocks, starting from |hero_z_| height. So all (x, y, z_i),
  // where (z_i >= hero_z_).
  std::vector<const Object*> GetWallColumn(int x, int y) const;

  // Assigns to |transparent_blocks_| left and right bottom walls of the
  // |current_room_|.
  void UpdateTransparentBlocks();

 private:
  std::vector<std::vector<std::vector<Object*>>> map_;
  std::unordered_set<const Object*> transparent_blocks_;
  std::vector<Room> rooms_;
  // First room in |rooms_| by default. Will be updated after 1 tick otherwise.
  Room current_room_{*rooms_.begin()};
  bool is_hero_on_the_room_edge_{false};
  int hero_z_{1};
};

#endif  // GAMEOBJECT_GAME_MAP_H_
