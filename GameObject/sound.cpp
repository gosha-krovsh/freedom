#include "sound.h"

Sound::Sound() {
  PlayTrack(kIdle, constants::kInfinity);
}

void Sound::PlayTrack(SoundAction action, int duration, int volume) {
  Track current{std::make_unique<QMediaPlayer>(),
                std::make_unique<QMediaPlaylist>(),
                duration};

  current.playlist->addMedia(QUrl(names_of_avaliable_songs_[action]));
  current.playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);

  current.player->setPlaylist(current.playlist.get());
  current.player->setVolume(volume * volume_coefficient_);
  current.player->play();

  tracks_.emplace_back(std::move(current));
}

void Sound::Tick(int) {
  for (int i = 0; i < tracks_.size(); ++i) {
    --tracks_[i].duration;
    if (tracks_[i].duration == 0) {
      tracks_.erase(tracks_.begin() + i);
      --i;
    }
  }
}

void Sound::SetVolumeCoefficient(double volume_coefficient) {
  volume_coefficient_ = volume_coefficient;
}
