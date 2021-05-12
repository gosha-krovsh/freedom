#ifndef GAMEOBJECT_SOUND_H_
#define GAMEOBJECT_SOUND_H_

#include <QMediaPlayer>
#include <QMediaPlaylist>

#include "Model/constants.h"

class Sound {
 public:
  enum SoundAction {
    kIdle = 0,
    kWallAttack = 1,
    kFight = 2
  };

  Sound();

  void SetTrack(SoundAction action, int duration);

  const int GetDuration() const;
  void Tick(int);

  int duration_{constants::kInfty};
 private:
  void Load();

  QMediaPlayer* player_ = new QMediaPlayer;
  QMediaPlaylist* playlist_ = new QMediaPlaylist;
};

#endif  // GAMEOBJECT_SOUND_H_
