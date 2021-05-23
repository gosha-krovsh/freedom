#ifndef VIEW_MAIN_MENU_H_
#define VIEW_MAIN_MENU_H_

#include <QWidget>
#include <QFile>
#include <QGridLayout>
#include <QLabel>
#include <QGraphicsBlurEffect>
#include <QPushButton>
#include <QStyleOption>
#include <QApplication>

#include "settings_menu.h"
#include "Controller/abstract_controller.h"

class MainMenu : public QWidget {
  Q_OBJECT

 public:
  explicit MainMenu(AbstractController* controller,
                    QWidget* parent = nullptr);
  ~MainMenu() override = default;

 private:
  // Draws background image.
  void paintEvent(QPaintEvent*) override;

  void SetUi();
  void SetStyles();
  void ConnectButtons();

 private:
  QPixmap background_image_{":main_menu_background.png"};
  AbstractController* controller_;
  QGridLayout* layout_;
  QPushButton* play_button_;
  QPushButton* settings_button_;
  QPushButton* exit_button_;
  SettingsMenu* settings_menu_;
};

#endif  // VIEW_MAIN_MENU_H_
