#ifndef VIEW_ITEM_BAR_H_
#define VIEW_ITEM_BAR_H_

#include <QDebug>
#include <QHBoxLayout>
#include <QHelpEvent>
#include <QPushButton>
#include <QWidget>

#include <algorithm>

#include "Model/constants.h"
#include "Controller/abstract_controller.h"

class ItemBar : QWidget {
 Q_OBJECT

 public:
  ItemBar(int x, int y, int height, int width,
          int id,
          AbstractController* controller,
          QWidget* parent = nullptr,
          StorableObject* storage = nullptr,
          Qt::WindowFlags f = Qt::WindowFlags());
  void Show();
  void Hide();
  void SetEnabled(bool);

  int GetId() const;
  StorableObject* GetObject() const;

  void UseItem(int index);

  void AssignObject(StorableObject*);
  void UpdateIcons();

 private:
  void SetUi(int x, int y, int width, int height);
  void ConnectButtons();
  void ButtonPressed(int index);
  void ClearIconsFromIndex(size_t index);

  AbstractController* controller_;
  StorableObject* storage_ = nullptr;
  int id_;

  std::vector<QPushButton*> buttons_;
  QHBoxLayout* layout_;
};

#endif  // VIEW_ITEM_BAR_H_
