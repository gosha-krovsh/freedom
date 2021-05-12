#include "sound.h"

Sound::Sound() {
  player_ = new QMediaPlayer;
  playlist_ = new QMediaPlaylist;
  playlist_->addMedia(QUrl("qrc:ost.mp3"));
  playlist_->addMedia(QUrl("qrc:wall.mp3"));
  playlist_->addMedia(QUrl("qrc:wall.mp3"));
  duration_ = constants::kInfty;
  playlist_->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
  player_->setPlaylist(playlist_);
  player_->play();
}
void Sound::SetTrack(SoundAction action, int duration) {
  playlist_->setCurrentIndex(action);
  duration_ = duration;
}
int& Sound::GetDuration() {
  return duration_;
}
