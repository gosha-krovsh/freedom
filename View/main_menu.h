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

  // Needs to be overrided in order to have possibility to set background image.
  void paintEvent(QPaintEvent*) override;

  void SetUi();
  void SetStyles();
  void ConnectButtons();

 private:
  AbstractController* controller_;
  QGridLayout* layout_;
  QPushButton* play_button_;
  QPushButton* settings_button_;
  QPushButton* exit_button_;
};

#endif  // VIEW_MAIN_MENU_H_
