#ifndef STATUS_BAR_H
#define STATUS_BAR_H

#include <QLabel>
#include <QFile>
#include <QGridLayout>

#include <map>
#include <set>

#include <Model/constants.h>
#include <Model/model.h>

class StatusBar : public QWidget {
  Q_OBJECT
 public:
  enum Type {
    kHealth,
    kAttack
  };

  StatusBar(const std::shared_ptr<Model>& model,
            QWidget* parent,
            int center_x,
            int y,
            int width,
            int height);

  void SetPrameter(Type type, const QString& param);

 private:
  void SetUi(int center_x, int y, int width, int height);
  void SetStyles();
  void SetCenterGeometry(int x, int y, int width, int height);
  void ConfigureStatus();

  QGridLayout* layout_;
  std::pair<QLabel*, QLabel*> health_status_;
  std::pair<QLabel*, QLabel*> attack_status_;

  std::shared_ptr<Model> model_;
};

#endif //STATUS_BAR_H
