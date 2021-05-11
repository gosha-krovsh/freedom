#ifndef SOUND_H
#define SOUND_H

#include <QMediaPlayer>
#include <QMediaPlaylist>

class Sound {
 public:
  explicit Sound();
  void SetTrack(int id);
 private:
  QMediaPlayer* player_;
  QMediaPlaylist* playlist_;

};

#endif //SOUND_H
