#include "conversation_window.h"

ConversationWindow::ConversationWindow(
    const Conversation& conversation,
    AbstractController* controller,
    QWidget* parent) : QWidget(parent),
    conversation_(conversation),
    controller_(controller),
    scroll_area_(new QScrollArea(this)),
    content_(new QWidget(this)),
    layout_(new QVBoxLayout(this)) {
  SetStyles();
  SetUi();
  AddNode();
  show();
}

void ConversationWindow::SetUi() {
  content_->setLayout(layout_);
  content_->setObjectName("content");
  layout_->setObjectName("layout");
  content_->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

  scroll_area_->setWidget(content_);
  scroll_area_->setWidgetResizable(true);
  scroll_area_->setAlignment(Qt::AlignCenter);
}

void ConversationWindow::SetStyles() {
  QFile styles(":conversation_window_styles");
  styles.open(QFile::ReadOnly);
  setStyleSheet(styles.readAll());
}

void ConversationWindow::resizeEvent(QResizeEvent*) {
  scroll_area_->setGeometry(0, 0, width(), height());
  content_->setGeometry(0.1 * width(), content_->y(),
                        0.8 * width(), content_->height());
}

void ConversationWindow::AddNode(int answer_index) {
  if (answer_index != - 1) {
    conversation_.MoveToNextNode(answer_index);
  }

  auto current_node = conversation_.GetCurrentNode();
  auto label = new QLabel(current_node.text, this);
  label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  label->setWordWrap(true);
  layout_->addWidget(label);

  if (conversation_.IsLastNode()) {
    auto ans_button = new QPushButton("Finish", this);
    ans_button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    layout_->addWidget(ans_button, Qt::AlignCenter);
    connect(ans_button, &QPushButton::pressed,
            this, [this]() {
              controller_->FinishConversation();
            });
  }

  std::vector<QPushButton*> ans_buttons;
  for (int i = 0; i < current_node.answers.size(); ++i) {
    auto ans_button = new QPushButton
        (QString::number(i + 1) + ". " + current_node.answers[i].text, this);
    ans_button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    layout_->addWidget(ans_button, Qt::AlignCenter);
    ans_buttons.emplace_back(ans_button);
  }

  for (int i = 0; i < ans_buttons.size(); ++i) {
    connect(ans_buttons[i], &QPushButton::pressed,
            this, [this, i, ans_buttons]() {
              // Disable all buttons
              for (const auto& bt : ans_buttons) {
                bt->setDisabled(true);
              }
              ans_buttons[i]->setObjectName("selected_answer_button");
              // Update StyleSheets for this button
              ans_buttons[i]->style()->unpolish(ans_buttons[i]);
              ans_buttons[i]->style()->polish(ans_buttons[i]);
              AddNode(i);
            });
  }
}
