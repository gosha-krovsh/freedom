#ifndef GAMEOBJECT_GAME_MAP_H_
#define GAMEOBJECT_GAME_MAP_H_

#include <QDebug>

#include <vector>
#include <unordered_set>

#include "object.h"

class GameMap {
 public:
  struct Room {
    Room(const QString& name,
         bool danger_zone,
         int bottom_left_x, int bottom_left_y,
         int up_right_x, int up_right_y);

    bool IsInside(int x, int y) const;
    bool IsInsideOrOnTheEdge(int x, int y) const;
    bool IsOnTheEdge(int x, int y) const;
    bool IsInside(const Room& room) const;

    bool operator==(const Room& rhs) const;
    bool operator!=(const Room& rhs) const;

    QString name;
    bool danger_zone;
    int down_left_x;
    int down_left_y;
    int up_right_x;
    int up_right_y;
  };

 public:
  GameMap() = default;
  GameMap(const GameMap&) = delete;
  GameMap& operator=(const GameMap&) = delete;
  GameMap(int x_size, int y_size, int z_size,
          const std::vector<Object*>& objects,
          const std::vector<Room>& rooms,
          int hero_z = 1);
  ~GameMap();

  void Tick(int current_tick);

  int GetXSize() const;
  int GetYSize() const;
  int GetZSize() const;

  // Returns the pointer to the object on the map. Returns the nullptr, if there
  // is an empty space, or if the x or y or z are out of range of map size.
  const Object* GetBlock(int x, int y, int z) const;
  Object* GetBlock(int x, int y, int z);

  Object* GetBlock(Point coords);
  const Object* GetBlock(Point coords) const;

  // Updates |current_room_| by hero coordinates. If hero is on the edge of the
  // room (usually it means in the doorway), we assume that he wants to go to
  // another room and that's why also update room in this case. This also makes
  // wall transparency effect prettier.
  void UpdateCurrentRoom(int hero_x, int hero_y);
  const Room& GetCurrentRoom() const;
  std::unordered_set<const Object*> GetTransparentBlocks() const;

 private:
  // Returns all blocks, starting from |hero_z_| height. So all (x, y, z_i),
  // where (z_i >= hero_z_).
  std::vector<const Object*> GetWallColumn(int x, int y) const;

  // Assigns to |transparent_blocks_| left and right bottom walls of the
  // |current_room_|.
  void UpdateTransparentBlocks();
  std::vector<Room>::const_iterator GetEdgeRoom(int hero_x, int hero_y) const;
  Room GetMostInnerRoom(int hero_x, int hero_y) const;

 private:
  std::vector<std::vector<std::vector<Object*>>> map_;
  std::unordered_set<const Object*> transparent_blocks_;
  std::vector<Room> rooms_;
  // Change default value to the room, where hero is spawned.
  Room current_room_{rooms_.at(0)};
  bool is_hero_on_the_room_edge_{false};
  int hero_z_{1};
};

#endif  // GAMEOBJECT_GAME_MAP_H_
