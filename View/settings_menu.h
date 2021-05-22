#ifndef VIEW_SETTINGS_MENU_H_
#define VIEW_SETTINGS_MENU_H_

#include <QWidget>
#include <QFile>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QStyleOption>
#include <QSlider>
#include <QTextEdit>
#include <QComboBox>
#include <QLineEdit>
#include <QSettings>

#include "Controller/abstract_controller.h"
#include "Model//settings.h"

class SettingsMenu : public QWidget {
  Q_OBJECT

 public:
  explicit SettingsMenu(AbstractController* controller,
                        QWidget* parent = nullptr);
  ~SettingsMenu() override = default;

 private:
  // Needs to be overrided in order to have possibility to work with
  // |QWidget#settings_menu| in |settings_menu_styles.qss|.
  void paintEvent(QPaintEvent*) override;
  void showEvent(QShowEvent*) override;

  void SetUi();
  void SetStyles();
  void ConnectButtons();
  void UpdateContent();
  void SaveData();

 private:
  AbstractController* controller_;
  QGridLayout* layout_;
  QSlider* volume_slider_;
  QComboBox* fps_combo_box_;
  QLineEdit* zoom_edit_;
  QPushButton* submit_button_;
  QPushButton* back_button_;
};

#endif  // VIEW_SETTINGS_MENU_H_
