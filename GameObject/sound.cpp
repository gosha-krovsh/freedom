#include "sound.h"

Sound::Sound() {
  Load();

  AddTrack(kIdle, constants::kInfinity);
}

void Sound::AddTrack(SoundAction action, int duration) {
  Track current{std::make_unique<QMediaPlayer>(),
                std::make_unique<QMediaPlaylist>(),
                duration};

  current.playlist->addMedia(QUrl(names_of_avaliable_songs_[action]));
  current.player->setPlaylist(current.playlist.get());
  current.player->play();
  tracks_.emplace_back(std::move(current));
}

int Sound::GetDuration() const {
  return duration_;
}

void Sound::Load() {
  // now kWallAttack and kFight are the same
}
void Sound::Tick(int) {
  // if (duration_ > 0) {
  //   player_->play();
  //   --duration_;
  // }
  //
  // if (duration_ == 0) {
  //   player_->stop();
  // }
}
