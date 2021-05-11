#include "sound.h"
Sound::Sound() {
  player_ = new QMediaPlayer;
  playlist_ = new QMediaPlaylist;
  playlist_->addMedia(QUrl("qrc:ost.mp3"));
  playlist_->addMedia(QUrl("qrc:wall.mp3"));
  playlist_->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
  player_->setPlaylist(playlist_);
  playlist_->setCurrentIndex(0);
  player_->play();
}
void Sound::SetTrack(int id) {
  playlist_->setCurrentIndex(1);
}
