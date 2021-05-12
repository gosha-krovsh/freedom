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
  current.playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
  current.player->setPlaylist(current.playlist.get());
  current.player->play();

  tracks_.emplace_back(std::move(current));
}

void Sound::Load() {
  // now kWallAttack and kFight are the same
}
void Sound::Tick(int) {
  for(auto& item : tracks_) {
    --item.duration;
    if (item.duration == 0) {
      item.player->stop();
      Track temp = std::move(tracks_.back());

      tracks_.back() = std::move(item);
      tracks_.pop_back();
      item = std::move(temp);
    }
  }
}

void Sound::Pop() {
  tracks_.back().player->stop();
  tracks_.pop_back();
}

void Sound::SetVolume(int volume) {
  for(auto& item : tracks_) {
    item.player->setVolume(volume);
  }
}

