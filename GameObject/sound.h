#ifndef GAMEOBJECT_SOUND_H_
#define GAMEOBJECT_SOUND_H_

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QSound>

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

  QMediaPlayer* player_ = new QMediaPlayer;
  QMediaPlaylist* playlist_ = new QMediaPlaylist;
  QMediaPlayer* background_player_ = new QMediaPlayer;
  QMediaPlaylist* background_playlist_ = new QMediaPlaylist;
};

#endif  // GAMEOBJECT_SOUND_H_
