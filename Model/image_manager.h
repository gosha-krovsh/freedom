#ifndef MODEL_IMAGE_MANAGER_H_
#define MODEL_IMAGE_MANAGER_H_

#include <QPixmap>

#include <map>
#include <memory>

class ImageManager {
 public:
  std::weak_ptr<QPixmap> GetImage(const QString& name);

 private:
  std::map<QString, std::shared_ptr<QPixmap>> images_;
};

#endif  // MODEL_IMAGE_MANAGER_H_
