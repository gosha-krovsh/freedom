#include <iostream>
#include "game_map.h"

// map store Z, X, Y
GameMap::GameMap(
    const std::vector<std::vector<std::vector<Object*>>>& objects,
    int hero_z) : map_(objects), hero_z_(hero_z) {
  // for (int z = 0; z < GetZSize(); ++z) {
  //   for (int x = 0; x < GetXSize(); ++x) {
  //     for (int y = 0; y < GetYSize(); ++y) {
  //       std::cout << map_[z][x][y] << " ";
  //     }
  //     std::cout << "\n";
  //   }
  //   std::cout << "\n";
  // }
}

// GameMap::GameMap(std::vector<Object>* objects, int hero_z) : hero_z_(hero_z) {
//   for (auto& object : *objects) {
//     map_[object.GetRoundedZ()]
//         [object.GetRoundedY()]
//         [object.GetRoundedX()] = &object;
//   }
// }

GameMap::~GameMap() {
  for (auto& surface : map_) {
    for (auto& line : surface) {
      for (auto& block : line) {
        delete block;
      }
    }
  }
}

int GameMap::GetXSize() const {
  return map_[0].size();
}

int GameMap::GetYSize() const {
  return map_[0][0].size();
}

int GameMap::GetZSize() const {
  return map_.size();
}

const Object* GameMap::GetBlock(int x, int y, int z) const {
  if ((x < 0) || (x >= GetXSize()) ||
      (y < 0) || (y >= GetYSize()) ||
      (z < 0) || (z >= GetZSize())) {
    return nullptr;
  }
  return map_[z][x][y];
}

std::unordered_set<const Object*>
    GameMap::GetTransparentBlocks(int hero_x, int hero_y) const {
  std::unordered_set<const Object*> result;
  for (int i = 1; i <= constants::kBlockTransparencyDistance; ++i) {
    auto corner = GetCorner(hero_x + i, hero_y + i);
    result.insert(corner.begin(), corner.end());
  }
  return result;
}

std::unordered_set<const Object*> GameMap::GetCorner(int x, int y) const {
  std::unordered_set<const Object*> result;

  // When there is a hall in the wall, we should consider only one wall
  if (!GetBlock(x, y, hero_z_)) {
    if (GetBlock(x, y - 1, hero_z_)) {
      auto left_wall = GetLeftWall(x, y - 1);
      result.insert(left_wall.begin(), left_wall.end());
    } else if (GetBlock(x - 1, y, hero_z_)) {
      auto right_wall = GetRightWall(x - 1, y);
      result.insert(right_wall.begin(), right_wall.end());
    }  // else: result is empty
    return result;
  }

  auto left_wall{GetLeftWall(x, y - 1)};
  result.insert(left_wall.begin(), left_wall.end());
  auto right_wall{GetRightWall(x - 1, y)};
  result.insert(right_wall.begin(), right_wall.end());

  // If Hero is standing right inside the corner, than 2 walls will be in the
  // |result|, but this column, that connects left and right wall - won't.
  // So we need to add it.
  auto current_column{GetWallColumn(x, y)};
  result.insert(current_column.begin(), current_column.end());

  return result;
}

std::vector<const Object*> GameMap::GetLeftWall(int x, int y) const {
  int y_begin = y;
  while (y_begin > 0 &&
        !IsBlockIntersection(x, y_begin - 1, x, y_begin)) {
    --y_begin;
  }

  int y_end = y;
  while (y_end < GetYSize() &&
        !IsBlockIntersection(x, y_end + 1, x, y_end)) {
    ++y_end;
  }

  std::vector<const Object*> result;
  for (int curr_y = y_begin; curr_y <= y_end; ++curr_y) {
    auto column = GetWallColumn(x, curr_y);
    result.insert(result.end(), column.begin(), column.end());
  }
  return result;
}

std::vector<const Object*> GameMap::GetRightWall(int x, int y) const {
  int x_begin = x;
  while (x_begin > 0 &&
        !IsBlockIntersection(x_begin - 1, y, x_begin, y)) {
    --x_begin;
  }

  int x_end = x;
  while (x_end < GetXSize() &&
        !IsBlockIntersection(x_end + 1, y, x_end, y)) {
    ++x_end;
  }

  std::vector<const Object*> result;
  for (int curr_x = x_begin; curr_x <= x_end; ++curr_x) {
    auto column = GetWallColumn(curr_x, y);
    result.insert(result.end(), column.begin(), column.end());
  }
  return result;
}

bool GameMap::IsBlockIntersection(int x, int y, int prev_x, int prev_y) const {
  int delta_x = x - prev_x;
  int delta_y = y - prev_y;
  for (int curr_z = hero_z_; curr_z < GetZSize(); ++curr_z) {
    if (GetBlock(x + delta_y, y + delta_x, curr_z) ||
        GetBlock(x - delta_y, y - delta_x, curr_z)) {
      return true;
    }
  }
  return false;
}

std::vector<const Object*> GameMap::GetWallColumn(int x, int y) const {
  std::vector<const Object*> result;
  result.reserve(GetZSize() - hero_z_);
  for (int curr_z = hero_z_; curr_z < GetZSize(); ++curr_z) {
    auto block = GetBlock(x, y, curr_z);
    if (block) {
      result.emplace_back(block);
    }
  }
  return result;
}
