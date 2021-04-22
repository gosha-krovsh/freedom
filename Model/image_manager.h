#ifndef MODEL_IMAGE_MANAGER_H_
#define MODEL_IMAGE_MANAGER_H_

#include <QPixmap>

#include <map>
#include <memory>

class ImageManager {
 public:
  static std::weak_ptr<QPixmap> GetImage(const QString& name);
  static void Wipe();

 private:
  static std::map<QString, std::weak_ptr<QPixmap>> images_;
};

#endif  // MODEL_IMAGE_MANAGER_H_
