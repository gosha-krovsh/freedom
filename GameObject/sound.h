#ifndef GAMEOBJECT_SOUND_H_
#define GAMEOBJECT_SOUND_H_

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QSound>

#include <memory>
#include <utility>
#include <vector>

#include "Model/constants.h"
#include "Model/settings.h"

class Sound {
 public:
  enum SoundAction {
    kIntro = 0,
    kWallAttack = 1,
    kFight = 2,
    kOpenDoor = 3,
    kOpenChest = 4,
    kTakeItem = 5,
    kTalking = 6,
    kUseItem = 7,
    kButtonClick = 8,
  };

  Sound();

  void PlayTrack(SoundAction action, int volume = constants::kInitVolume);
  void PlayTrackOnce(SoundAction action, int volume = constants::kInitVolume);
  void UpdateDurations();
  void UpdateSettings();

  void Tick(int);
  void SetVolumeCoefficient(double volume_coefficient);
  void RemoveAllTracks();
  void PauseAllTracks();
  void ResumeAllTracks();

 private:
  struct Track {
    std::unique_ptr<QMediaPlayer> player;
    std::unique_ptr<QMediaPlaylist> playlist;
    int duration;
    int volume;
  };

  double volume_coefficient_ = 1;
  std::vector<Track> tracks_;
  std::vector<std::pair<QString, int>> song_names_and_durations_;
};

#endif  // GAMEOBJECT_SOUND_H_
