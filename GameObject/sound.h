#ifndef GAMEOBJECT_SOUND_H_
#define GAMEOBJECT_SOUND_H_

#include <QMediaPlayer>
#include <QMediaPlaylist>

#include "Model/constants.h"

class Sound {
 public:
  enum SoundAction {
    kIdle = 0,
    kFightWall = 1,
    kFightHero = 2
  };

  Sound();

  void SetTrack(SoundAction action, int duration);
  int& GetDuration();
  const int& GetDuration() const;

 private:
  QMediaPlayer* player_;
  QMediaPlaylist* playlist_;
  int duration_;
};

#endif  // GAMEOBJECT_SOUND_H_