#include "game_widget.h"

GameWidget::GameWidget(const std::shared_ptr<Model>& model) : model_(model) {
  setAutoFillBackground(true);
}

void GameWidget::CenterCameraOnHero(QPainter* camera) const {
  // Get center of screen
  double x_camera_offset = width() / 2.;
  double y_camera_offset = height() / 2.;

  // Center camera on center of |Hero|
  x_camera_offset -= (model_->GetHero().GetCoordinates().GetIsometricX() + 1)
      * (Settings::kBlockSize / 2.);
  y_camera_offset -= (model_->GetHero().GetCoordinates().GetIsometricY() + 1)
      * (Settings::kBlockSize / 2.);

  // Make camera follow |Hero|
  camera->translate(x_camera_offset, y_camera_offset);
}

void GameWidget::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  CenterCameraOnHero(&painter);

  const Hero& hero = model_->GetHero();
  const GameMap& map = model_->GetMap();
  const auto& bots = model_->GetBots();
  std::unordered_set<const Object*>
      transparent_blocks = map.GetTransparentBlocks();

  for (int z = 0; z < map.GetZSize(); ++z) {
    for (int y = 0; y < map.GetYSize(); ++y) {
      for (int x = 0; x < map.GetXSize(); ++x) {
        auto curr_block = map.GetBlock(x, y, z);
        if (curr_block) {
          if (transparent_blocks.find(curr_block) != transparent_blocks.end()) {
            painter.setOpacity(constants::kBlockOpacity);
          }
          curr_block->Draw(&painter);
          painter.setOpacity(1);
        }

        bool hero_drown = false;
        Point camera = Point(map.GetXSize(), map.GetYSize());
        double hero_distance_to_camera =
            hero.GetCoordinates().DistanceFrom(camera);

        for (const auto& current_bot : bots) {
          double bot_distance_to_camera =
              current_bot->GetCoordinates().DistanceFrom(camera);

          if (hero.GetRoundedX() == x &&
              hero.GetRoundedY() == y &&
              hero.GetRoundedZ() == z &&
              hero_distance_to_camera > bot_distance_to_camera) {
            hero.Draw(&painter);
            hero_drown = true;
          }
          if (current_bot->GetRoundedX() == x &&
              current_bot->GetRoundedY() == y &&
              current_bot->GetRoundedZ() == z) {
            double dist = hero.GetCoordinates().
                DistanceFrom(current_bot->GetCoordinates());

            if (!current_bot->IsAbleToAttack()) {
              painter.setOpacity(1);
            } else {
              painter.setOpacity(std::max(dist / 2,
                                          constants::kBotOpacity));
            }
            current_bot->Draw(&painter);
            painter.setOpacity(1);
            QFont font = painter.font();
            font.setPointSize(30);
            painter.setFont(font);
            auto text_coords = current_bot->GetCoordinates();
            int x = static_cast<int>((text_coords.GetIsometricX() + 0.5) *
                (Settings::kBlockSize / 2.));
            int y = static_cast<int>((text_coords.GetIsometricY() + 0.4) *
                (Settings::kBlockSize / 2.));
            painter.drawText(x, y, current_bot->GetName());
          }
        }

        if (!hero_drown &&
            hero.GetRoundedX() == x &&
            hero.GetRoundedY() == y &&
            hero.GetRoundedZ() == z) {
          hero.Draw(&painter);
        }
      }
    }
  }
}
