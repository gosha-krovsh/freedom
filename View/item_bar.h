#ifndef VIEW_ITEM_BAR_H_
#define VIEW_ITEM_BAR_H_

#include <QDebug>
#include <QHBoxLayout>
#include <QHelpEvent>
#include <QPushButton>
#include <QWidget>

#include <algorithm>
#include <memory>
#include <vector>

#include "Model/constants.h"
#include "Controller/abstract_controller.h"

class ItemBar : public QWidget {
 Q_OBJECT

 public:
  ItemBar(int id,
          AbstractController* controller,
          QWidget* parent = nullptr,
          const std::shared_ptr<Storage>& storage = nullptr,
          Qt::WindowFlags f = Qt::WindowFlags());

  int GetId() const;
  std::shared_ptr<Storage> GetStorage() const;

  void UseItem(int index);

  void AssignStorage(const std::shared_ptr<Storage>& object);
  void UpdateIcons();
  void ResizeButtons(int width, int max_height);

 private:
  void SetUi();
  void ConnectButtons();
  void ButtonPressed(int index);
  void ClearIconsFromIndex(int index);
  void SetStyles();
  void resizeEvent(QResizeEvent*) override;

  AbstractController* controller_;
  std::shared_ptr<Storage> storage_ = nullptr;
  int id_;

  std::vector<QPushButton*> buttons_;
  QHBoxLayout* layout_;
};

#endif  // VIEW_ITEM_BAR_H_
