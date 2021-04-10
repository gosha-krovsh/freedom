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
    QString name;
    int bottom_left_x;
    int bottom_left_y;
    int up_right_x;
    int up_right_y;

    bool IsInsideRoom(int x, int y) const;
    bool operator<(const Room& rhs) const;
  };

 public:
  GameMap() = default;
  GameMap(int x_size, int y_size, int z_size,
          const std::vector<Object*>& objects,
          const std::set<Room>& rooms,
          int hero_z = 1);
  ~GameMap();

  int GetXSize() const;
  int GetYSize() const;
  int GetZSize() const;
  const Object* GetBlock(int x, int y, int z) const;

  void UpdateCurrentRoom(int hero_x, int hero_y);
  std::unordered_set<const Object*> GetTransparentBlocks() const;

 private:
  // Returns all blocks, starting from |hero_z_| height. So all (x, y, z_i),
  // where (z_i >= hero_z_).
  std::vector<const Object*> GetWallColumn(int x, int y) const;
  void UpdateTransparentBlocks();

 private:
  std::vector<std::vector<std::vector<Object*>>> map_;
  std::unordered_set<const Object*> transparent_blocks_;
  std::set<Room> rooms_;
  // First room in |rooms_| by default. Will be updated after 1 tick otherwise.
  Room current_room_;
  int hero_z_{1};
};

#endif  // GAMEOBJECT_GAME_MAP_H_
