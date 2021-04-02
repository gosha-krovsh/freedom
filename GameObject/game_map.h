#ifndef GAMEOBJECT_GAME_MAP_H_
#define GAMEOBJECT_GAME_MAP_H_

#include <vector>
#include <unordered_set>

#include "object.h"

class GameMap {
 public:
  GameMap() = default;
  GameMap(std::vector<Object>* objects, int hero_z);

  int GetXSize() const;
  int GetYSize() const;
  int GetZSize() const;

  const Object* GetBlock(int x, int y, int z) const;

  // Returns blocks, which should be transparent, by hero (x, y) coordinates.
  // These blocks include all corners at distance from 1 to
  // |kBlockTransparencyDistance| blocks from the |Hero|.
  std::unordered_set<const Object*>
      GetTransparentBlocks(int hero_x, int hero_y) const;

 private:
  // Returns together left and(or) right walls of (x, y) block.
  std::unordered_set<const Object*> GetCorner(int x, int y) const;

  // Returns the left (i.e. going in |y| direction) wall of blocks, where
  // (x, y) is situated.
  std::vector<const Object*> GetLeftWall(int x, int y) const;

  // Returns the right (i.e. going in |x| direction) wall of blocks, where
  // (x, y) is situated.
  std::vector<const Object*> GetRightWall(int x, int y) const;

  // Returns true, if when going in (prev_x, prev_y)->(x, y) direction
  // (on any height) the orthogonal line of block crosses our direction in
  // (x, y) point, i.e. there is the intersection of 2 orthogonal lines.
  // Pay attention: there can be no block in (prev_x, prev_y)! It's just the
  // direction.
  bool IsBlockIntersection(int x, int y, int prev_x, int prev_y) const;

  // Returns all blocks, except floor, which are situated in (x, y).
  // So all (x, y, z_i), where (z_i != 0)
  std::vector<const Object*> GetWallColumn(int x, int y) const;

 private:
  std::vector<std::vector<std::vector<Object*>>>
      map_{std::vector<std::vector<std::vector<Object*>>>(
           constants::kMapSizeZ, std::vector<std::vector<Object*>>(
           constants::kMapSizeY, std::vector<Object*>(
           constants::kMapSizeX, nullptr)))};
  int hero_z_{1};
};

#endif  // GAMEOBJECT_GAME_MAP_H_
