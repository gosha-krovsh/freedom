#include "quest_task_list.h"

QuestTaskList::QuestTaskList(
    AbstractController* controller,
    QWidget* parent) :
    QWidget(parent),
    controller_(controller),
    scroll_area_(new QScrollArea(this)),
    content_(new QWidget(this)),
    layout_(new QVBoxLayout(this)) {
  SetUi();
  SetStyles();
  hide();
}

void QuestTaskList::resizeEvent(QResizeEvent*) {
  scroll_area_->setGeometry(0, 0, width(), height());
}

void QuestTaskList::SetUi() {
  content_->setLayout(layout_);
  content_->setObjectName("content");
  content_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  scroll_area_->setWidget(content_);
  scroll_area_->setWidgetResizable(true);
  scroll_area_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

  // Autoscroll to the end. When there are many answers on a small screen, the
  // question can be not seen. Can memorize position of question labels and set
  // value here somehow, but on big screens with a few answers everything
  // will be OK.
  auto scroll_bar = scroll_area_->verticalScrollBar();
  connect(scroll_bar, &QScrollBar::rangeChanged,
          this, [scroll_bar]() {
        scroll_bar->setValue(scroll_bar->maximum());
      });

  setFocus();
}

void QuestTaskList::SetQuestString(const QString& quest_name,
                                   const std::vector<QString>& node_strings) {
  if (quest_string_.find(quest_name) != quest_string_.end()) {
    return;
  } else if (quest_string_.empty()) {
    show();
  }

  quest_string_.insert(std::make_pair(quest_name, node_strings));

  QLabel* quest_label = new QLabel(content_);
  quest_label->setText(quest_name);
  quest_label->setObjectName("quest_label");
  layout_->addWidget(quest_label);

  std::vector<QLabel*> labels;
  labels.reserve(node_strings.size());
  for (auto& node : node_strings) {
    QLabel* label = new QLabel(content_);
    label->setText(node);
    label->setObjectName("node_label");
    layout_->addWidget(label);

    labels.push_back(label);
  }
  quest_labels_.insert(std::make_pair(quest_name,
                                      std::make_pair(quest_label, labels)));
}

void QuestTaskList::DeleteQuest(const QString& quest) {
  quest_string_.erase(quest);

  QLabel* quest_label = quest_labels_.at(quest).first;
  delete quest_label;

  for (auto& label : quest_labels_.at(quest).second) {
    delete label;
  }
  quest_labels_.erase(quest);

  if (quest_string_.empty()) {
    hide();
  }
}

void QuestTaskList::UpdateCurrentLables(const QString& quest_name,
                                        int index) {
  std::vector<QLabel*> node_lables = quest_labels_.at(quest_name).second;

  int max_index = 0;
  for (auto& node_label : node_lables) {
    if (max_index >= index) {
      return;
    }

    node_label->setText("<s>" + node_label->text() + "</s>");
    max_index++;
  }
}

void QuestTaskList::SetStyles() {
  QFile styles(":quest_task_list_styles");
  styles.open(QFile::ReadOnly);
  setStyleSheet(styles.readAll());
}
