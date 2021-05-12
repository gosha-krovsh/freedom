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
    kIdle = 0,
    kWallAttack = 1,
    kFight = 1
  };

  Sound();

  void AddTrack(SoundAction action, int duration);

  void Pop();
  void Tick(int);
  void SetVolume(int volume);

 private:
  struct Track {
    std::unique_ptr<QMediaPlayer> player;
    std::unique_ptr<QMediaPlaylist> playlist;
    int duration;
  };

  void Load();

  std::vector<Track> tracks_;
  std::vector<QString>
  names_of_avaliable_songs_ {"qrc:idle.mp3", "qrc:wall.mp3"};
};

#endif  // GAMEOBJECT_SOUND_H_
