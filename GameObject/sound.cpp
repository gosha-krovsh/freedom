#include "sound.h"

Sound::Sound() {
  Load();

  playlist_->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
  player_->setPlaylist(playlist_);
  player_->play();
}

void Sound::SetTrack(SoundAction action, int duration) {
  playlist_->setCurrentIndex(action);
  duration_ = duration;
}

const int Sound::GetDuration() const {
  return duration_;
}

void Sound::Load() {
  playlist_->addMedia(QUrl("qrc:ost.mp3"));
  playlist_->addMedia(QUrl("qrc:wall.mp3"));
  playlist_->addMedia(QUrl("qrc:wall.mp3"));
  // now kWallAttack and kFight are the same
}
void Sound::Tick(int) {
  if (duration_ > 0) {
    --duration_;
  }

  if (duration_ == 0) {
    SetTrack(Sound::kIdle, constants::kInfty);
  }
}
