#include <iostream>
#include "view.h"

View::View(AbstractController* controller,
           std::shared_ptr<Model> model) : controller_(controller),
                           model_(model),
                           timer_(new QTimer(this)) {
  setMinimumSize(constants::kWindowWidth, constants::kWindowHeight);

  connect(timer_, &QTimer::timeout, this, &View::TimerEvent);
  timer_->start(1000 / constants::kFPS);

  show();
}

void View::paintEvent(QPaintEvent*) {
  QPainter painter(this);

  const Hero& hero = model_->GetHero();
  const auto& map = model_->GetMap();

  std::vector<const Object*> transparent_blocks;
  if (hero.GetFlooredY() + 1 < map[hero.GetRoundedZ()].size() &&
      hero.GetFlooredX() + 1 < map[hero.GetRoundedZ()][hero.GetFlooredY() + 1].size()) {
    const Object* main_overlapping_block =
        map[hero.GetRoundedZ()][hero.GetFlooredY() + 1][hero.GetFlooredX() + 1];
    if (main_overlapping_block) {
      transparent_blocks.push_back(main_overlapping_block);
      // в классе map сделать метод GetWallByItsBlock() (нужно влево-вправо и вверх!)
      int curr_y = main_overlapping_block->GetRoundedY() - 1;
      while (curr_y >= 0 &&
          map[main_overlapping_block->GetRoundedZ()]
          [curr_y]
          [main_overlapping_block->GetRoundedX()]) {
        transparent_blocks.push_back(map[main_overlapping_block->GetRoundedZ()]
                                     [curr_y]
                                     [main_overlapping_block->GetRoundedX()]);
        --curr_y;
      }

      int curr_x = main_overlapping_block->GetRoundedX() - 1;
      while (curr_x >= 0 &&
          map[main_overlapping_block->GetRoundedZ()]
          [main_overlapping_block->GetRoundedY()]
          [curr_x]) {
        transparent_blocks.push_back(map[main_overlapping_block->GetRoundedZ()]
                                     [main_overlapping_block->GetRoundedY()]
                                     [curr_x]);
        --curr_x;
      }
    }
  }


  for (int z = 0; z < map.size(); ++z) {
    for (int y = 0; y < map[z].size(); ++y) {
      for (int x = 0; x < map[z][y].size(); ++x) {
        if (map[z][y][x]) {
          if (std::find(transparent_blocks.begin(), transparent_blocks.end(),
                        map[z][y][x]) != transparent_blocks.end()) {
            painter.setOpacity(0.1);
          }
          map[z][y][x]->Draw(&painter);
          painter.setOpacity(1);
        }

        if (hero.GetRoundedX() == x &&
            hero.GetRoundedY() == y &&
            hero.GetRoundedZ() == z) {
          hero.Draw(&painter);
        }
      }
    }
  }
}

void View::TimerEvent() {
  controller_->Tick();
  repaint();
}

void View::keyPressEvent(QKeyEvent* event) {
  switch (event->key()) {
    case Qt::Key_Up:
    case Qt::Key_W: {
      controller_->SetControlUpKeyState(true);
      break;
    }
    case Qt::Key_Right:
    case Qt::Key_D: {
      controller_->SetControlRightKeyState(true);
      break;
    }
    case Qt::Key_Down:
    case Qt::Key_S: {
      controller_->SetControlDownKeyState(true);
      break;
    }
    case Qt::Key_Left:
    case Qt::Key_A: {
      controller_->SetControlLeftKeyState(true);
      break;
    }
  }
}

void View::keyReleaseEvent(QKeyEvent* event) {
  switch (event->key()) {
    case Qt::Key_Up:
    case Qt::Key_W: {
      controller_->SetControlUpKeyState(false);
      break;
    }
    case Qt::Key_Right:
    case Qt::Key_D: {
      controller_->SetControlRightKeyState(false);
      break;
    }
    case Qt::Key_Down:
    case Qt::Key_S: {
      controller_->SetControlDownKeyState(false);
      break;
    }
    case Qt::Key_Left:
    case Qt::Key_A: {
      controller_->SetControlLeftKeyState(false);
      break;
    }
  }
}

void View::changeEvent(QEvent* event) {
  if (event->type() == QEvent::ActivationChange && !isActiveWindow()) {
    controller_->SetControlUpKeyState(false);
    controller_->SetControlRightKeyState(false);
    controller_->SetControlDownKeyState(false);
    controller_->SetControlLeftKeyState(false);
  }
}
