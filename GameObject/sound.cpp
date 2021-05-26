#include "sound.h"

Sound::Sound() {
  UpdateSettings();
  PlayTrack(kBackground);
}

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

void Sound::PlayTrackOnce(Sound::SoundAction action, int volume) {
  Track current{std::make_unique<QMediaPlayer>(),
                std::make_unique<QMediaPlaylist>(),
                song_names_and_durations_[action].second,
                volume};

  current.playlist->addMedia(QUrl(song_names_and_durations_[action].first));
  current.playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);

  current.player->setPlaylist(current.playlist.get());
  current.player->setVolume(current.volume * volume_coefficient_);
  current.player->play();

  tracks_.emplace_back(std::move(current));
}

void Sound::Tick(int) {
  for (int i = 0; i < tracks_.size(); ++i) {
    --tracks_[i].duration;
    if (tracks_[i].duration <= 0) {
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

void Sound::PauseAllTracks() {
  // The first track is always Background
  for (int i = 1; i < tracks_.size(); ++i) {
    tracks_[i].player->pause();
  }
}

void Sound::ResumeAllTracks() {
  // The first track is always Background
  for (int i = 1; i < tracks_.size(); ++i) {
    tracks_[i].player->play();
  }
}

void Sound::UpdateDurations() {
  song_names_and_durations_ = {
      {"qrc:background.mp3", constants::kInfinity},
      {"qrc:wall_attack.mp3", Settings::GetDurationOfShaking()},
      {"qrc:wall_attack.mp3", Settings::GetAttackCooldown()},
      {"qrc:door_open.mp3", Settings::GetDefaultSoundDuration()},
      {"qrc:chest_open.mp3", Settings::GetDefaultSoundDuration()},
      {"qrc:take_item.mp3", Settings::GetDefaultSoundDuration()},
      {"qrc:talking.mp3", 0},
      {"qrc:use_item.mp3", Settings::GetDefaultSoundDuration()},
      {"qrc:button_click.mp3", 0},
  };
}

void Sound::UpdateSettings() {
  UpdateDurations();
  SetVolumeCoefficient(static_cast<double>(Settings::kVolume) /
                                           constants::kInitVolume);
}
