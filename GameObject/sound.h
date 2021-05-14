#ifndef GAMEOBJECT_SOUND_H_
#define GAMEOBJECT_SOUND_H_

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QSound>

#include <memory>
#include <utility>
#include <vector>

#include "Model/constants.h"

class Sound {
 public:
  enum SoundAction {
    kIdle = 0,
    kWallAttack = 1,
    kFight = 1
  };

  Sound();

  void PlayTrack(SoundAction action, int duration, int volume = 100);

  void Tick(int);
  void SetVolumeCoefficient(double volume_coefficient);

 private:
  struct Track {
    std::unique_ptr<QMediaPlayer> player;
    std::unique_ptr<QMediaPlaylist> playlist;
    int duration;
  };

  double volume_coefficient_ = 1;
  std::vector<Track> tracks_;
  std::vector<QString> names_of_avaliable_songs_{
    "qrc:idle.mp3", "qrc:wall_attack.mp3"};
};

#endif  // GAMEOBJECT_SOUND_H_
