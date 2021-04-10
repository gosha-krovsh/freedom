#include "game_map.h"

bool GameMap::Room::IsInsideRoom(int x, int y) const {
  return (x <= bottom_left_x &&
          x >= up_right_x &&
          y >= bottom_left_y &&
          y <= up_right_y);
}

bool GameMap::Room::operator<(const GameMap::Room& rhs) const {
  return (name < rhs.name);
}

// ----------------------------------------------------------------------------

GameMap::GameMap(int x_size, int y_size, int z_size,
                 const std::vector<Object*>& objects,
                 const std::set<Room>& rooms,
                 int hero_z) :
                 map_(std::vector<std::vector<std::vector<Object*>>>(
                            z_size, std::vector<std::vector<Object*>>(
                                x_size, std::vector<Object*>(
                                    y_size, nullptr)))),
                 rooms_(rooms),
                 hero_z_(hero_z),
                 current_room_(*rooms.begin()) {
  for (auto& object : objects) {
    if (object) {
      map_[object->GetRoundedZ()]
          [object->GetRoundedX()]
          [object->GetRoundedY()] = object;
    }
  }
  // Otherwise, won't be updated after a tick, if hero will be in the 1 room.
  UpdateTransparentBlocks();
}

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

std::unordered_set<const Object*> GameMap::GetTransparentBlocks() const {
  return transparent_blocks_;
}

void GameMap::UpdateCurrentRoom(int hero_x, int hero_y) {
  if (current_room_.IsInsideRoom(hero_x, hero_y)) {
    return;
  }

  auto room_iter = std::find_if(rooms_.begin(), rooms_.end(),
                                [hero_x, hero_y](const Room& room) {
                                  return room.IsInsideRoom(hero_x, hero_y);
                                });
  if (room_iter == rooms_.end()) {
    qDebug() << "Hero coordinates does not belong to any room";
    return;
  }

  current_room_ = *room_iter;
  UpdateTransparentBlocks();
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

void GameMap::UpdateTransparentBlocks() {
  transparent_blocks_.clear();
  for (int x = current_room_.up_right_x + 1;
       x <= current_room_.bottom_left_x; ++x) {
    auto column = GetWallColumn(x, current_room_.up_right_y);
    transparent_blocks_.insert(column.begin(), column.end());
  }
  for (int y = current_room_.bottom_left_y + 1;
       y < current_room_.up_right_y; ++y) {
    auto column = GetWallColumn(current_room_.bottom_left_x, y);
    transparent_blocks_.insert(column.begin(), column.end());
  }
}
