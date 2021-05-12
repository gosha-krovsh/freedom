#include "sound.h"

Sound::Sound() {
  Load();

  playlist_->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
  player_->setPlaylist(playlist_.get());
  player_->play();

  background_playlist_->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
  background_player_->setPlaylist(background_playlist_.get());
  background_player_->setVolume(50);
  background_player_->play();
}

void Sound::SetTrack(SoundAction action, int duration) {
  playlist_->setCurrentIndex(action);
  duration_ = duration;
}

int Sound::GetDuration() const {
  return duration_;
}

void Sound::Load() {
  background_playlist_->addMedia(QUrl("qrc:idle.mp3"));

  playlist_->addMedia(QUrl("qrc:wall.mp3"));
  playlist_->addMedia(QUrl("qrc:wall.mp3"));
  // now kWallAttack and kFight are the same
}
void Sound::Tick(int) {
  if (duration_ > 0) {
    player_->play();
    --duration_;
  }

  if (duration_ == 0) {
    player_->stop();
  }
}
