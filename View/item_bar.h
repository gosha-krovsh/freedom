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

class ItemBar : public QWidget {
 Q_OBJECT

 public:
  ItemBar(int id,
          AbstractController* controller,
          QWidget* parent = nullptr,
          StorableObject* storage = nullptr,
          Qt::WindowFlags f = Qt::WindowFlags());

  int GetId() const;
  StorableObject* GetObject() const;

  void UseItem(int index);

  void AssignObject(StorableObject*);
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
  StorableObject* storage_ = nullptr;
  int id_;

  std::vector<QPushButton*> buttons_;
  QHBoxLayout* layout_;
};

#endif  // VIEW_ITEM_BAR_H_
