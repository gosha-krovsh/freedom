#include "sound.h"

void Sound::PlayTrack(SoundAction action, int volume) {
  Track current{std::make_unique<QMediaPlayer>(),
                std::make_unique<QMediaPlaylist>(),
                song_names_and_durations_[action].second,
                volume};

  current.playlist->addMedia(QUrl(song_names_and_durations_[action].first));
  current.playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);

  current.player->setPlaylist(current.playlist.get());
  current.player->setVolume(current.volume * volume_coefficient_);
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
  for (auto& track : tracks_) {
    track.player->setVolume(track.volume * volume_coefficient_);
  }
}

void Sound::RemoveAllTracks() {
  PauseAllTracks();
  tracks_.clear();
}

void Sound::PauseAllTracks() {
  for (int i = 0; i < tracks_.size(); ++i) {
    tracks_[i].player->pause();
  }
}

void Sound::ResumeAllTracks() {
  for (int i = 0; i < tracks_.size(); ++i) {
    tracks_[i].player->play();
  }
}
