#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include <QKeyEvent>
#include <QMainWindow>
#include <QTimer>

#include <algorithm>
#include <memory>
#include <unordered_set>
#include <utility>
#include <vector>

#include "View/bar_pack.h"
#include "View/status_bar.h"
#include "View/quest_task_list.h"
#include "game_widget.h"
#include "bar_pack.h"
#include "conversation_window.h"
#include "main_menu.h"
#include "Controller/abstract_controller.h"
#include "Model/model.h"
#include "Model/settings.h"
#include "GameObject/object.h"

class View : public QMainWindow {
  Q_OBJECT

 public:
  View(AbstractController* controller, const std::shared_ptr<Model>& model);
  void Show();

  void CloseConversationWindow();
  void CloseMainMenu();
  // Makes a pair of 2 bars, where first argument is a source
  // and second is a destination
  std::pair<ItemBar*, ItemBar*> GetSrcDestBars(int id, int index);
  // Opens the second bar, when clicked
  // and there is an object that can store something nearby
  void ItemDialogEvent();
  bool IsItemDialogOpen() const;
  void StartConversation(const std::shared_ptr<Conversation>& conversation);
  void ShowGame();
  void HideGame();
  void ShowMainMenu();

  // After storage is parsed from json it should be reassigned to hero
  void AssignHeroStorage();

  void UpdateStatusBar();

  void AddQuestToTaskList(const QString& quest_name,
                          const std::vector<QString>& node_strings);
  void UpdateQuestTaskList(const QString& quest_name, int index);

  BarPack* GetBarPack();
  QuestTaskList* GetQuestTaskList();

 private:
  void SetUi();
  void SetStyles();

  void resizeEvent(QResizeEvent*) override;
  void keyPressEvent(QKeyEvent*) override;
  void keyReleaseEvent(QKeyEvent*) override;
  void changeEvent(QEvent*) override;
  void TimerEvent();

  void StartTickTimer();
  void StopTickTimer();

  bool IsInputBlocked() const;
  void InterruptAllInput();

  void SetHealth(int health);
  void SetAttack(int attack);
  void SetTime(const Time& time);
  void SetLocation(const QString& location_str);

 private:
  QTimer* timer_{new QTimer(this)};
  AbstractController* controller_;
  std::shared_ptr<Model> model_;
  std::unique_ptr<GameWidget> game_widget_;

  bool is_item_dialog_open_{false};
  BarPack* item_bar_pack_;
  StatusBar* status_bar_;
  QuestTaskList* task_list_;

  QLabel* time_label_{new QLabel(game_widget_.get())};
  QLabel* location_label_{new QLabel(game_widget_.get())};

  std::unique_ptr<ConversationWindow> conversation_window_{nullptr};
  std::unique_ptr<MainMenu> main_menu_{nullptr};
};

#endif  // VIEW_VIEW_H_
