#ifndef GAMEOBJECT_SOUND_H_
#define GAMEOBJECT_SOUND_H_

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QSound>

#include <memory>

#include "Model/constants.h"

class Sound {
 public:
  enum SoundAction {
    kWallAttack = 0,
    kFight = 1
  };

  Sound();

  void SetTrack(SoundAction action, int duration);

  int GetDuration() const;
  void Tick(int);

  int duration_{0};

 private:
  void Load();

  std::unique_ptr<QMediaPlayer> player_ = std::make_unique<QMediaPlayer>();
  std::unique_ptr<QMediaPlaylist> playlist_ =
      std::make_unique<QMediaPlaylist>();
  std::unique_ptr<QMediaPlayer> background_player_ =
      std::make_unique<QMediaPlayer>();
  std::unique_ptr<QMediaPlaylist> background_playlist_ =
      std::make_unique<QMediaPlaylist>();
};

#endif  // GAMEOBJECT_SOUND_H_
