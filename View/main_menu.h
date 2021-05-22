#ifndef VIEW_MAIN_MENU_H_
#define VIEW_MAIN_MENU_H_

#include <QWidget>
#include <QFile>
#include <QGridLayout>
#include <QLabel>

#include "Controller/abstract_controller.h"

class MainMenu : public QWidget {
  Q_OBJECT

 public:
  explicit MainMenu(AbstractController* controller,
                    QWidget* parent = nullptr);
  ~MainMenu() override = default;

 private:
  // void resizeEvent(QResizeEvent*) override;
  // void keyPressEvent(QKeyEvent*) override;

  void SetUi();
  void SetStyles();

 private:
  AbstractController* controller_;
  QGridLayout* layout_;
};

#endif  // VIEW_MAIN_MENU_H_
