#include "conversation_window.h"

ConversationWindow::ConversationWindow(
    const Conversation& conversation,
    AbstractController* controller,
    QWidget* parent) :
    QWidget(parent),
    conversation_(conversation),
    controller_(controller),
    scroll_area_(new QScrollArea(this)),
    content_(new QWidget(this)),
    layout_(new QVBoxLayout(this)) {
  SetUi();
  SetStyles();
  AddNextNode();
  show();
}

void ConversationWindow::SetUi() {
  content_->setLayout(layout_);
  content_->setObjectName("content");
  content_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  scroll_area_->setWidget(content_);
  scroll_area_->setWidgetResizable(true);

  setFocus();
}

void ConversationWindow::SetStyles() {
  QFile styles(":conversation_window_styles");
  styles.open(QFile::ReadOnly);
  setStyleSheet(styles.readAll());
}

void ConversationWindow::resizeEvent(QResizeEvent*) {
  scroll_area_->setGeometry(0, 0, width(), height());
}

void ConversationWindow::AddNextNode(int answer_index) {
  if (answer_index != - 1) {
    conversation_.MoveToNextNode(answer_index);
  }

  auto current_node = conversation_.GetCurrentNode();
  CreateConversationLabel(current_node.text);

  if (conversation_.IsLastNode()) {
    CreateFinishConversationButton();
  }

  // Creates all answer buttons
  current_ans_buttons_.clear();
  for (int i = 0; i < current_node.answers.size(); ++i) {
    auto button = CreateAnswerButton(i, current_node.answers[i].text);
    current_ans_buttons_.emplace_back(button);
  }

  // Connects all answer buttons presses
  for (int i = 0; i < current_ans_buttons_.size(); ++i) {
    connect(current_ans_buttons_[i], &QPushButton::pressed,
            this, [this, i] {
          AnswerButtonPress(i);
    });
  }
}

void ConversationWindow::AnswerButtonPress(int answer_index) {
  // Disable all buttons
  for (const auto& button : current_ans_buttons_) {
    button->setDisabled(true);
  }

  // Update StyleSheets for selected button
  current_ans_buttons_[answer_index]->setObjectName("selected_answer_button");
  current_ans_buttons_[answer_index]->style()->unpolish(current_ans_buttons_[answer_index]);
  current_ans_buttons_[answer_index]->style()->polish(current_ans_buttons_[answer_index]);

  AddNextNode(answer_index);
}

QPushButton* ConversationWindow::CreateAnswerButton(
    int answer_index, const QString& answer_text) {
  QString button_text = QString::number(answer_index + 1) + ". " + answer_text;
  QPushButton* ans_button = new QPushButton(button_text, this);
  ans_button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  ans_button->setObjectName("answer_button");
  layout_->addWidget(ans_button);
  return ans_button;
}

QLabel* ConversationWindow::CreateConversationLabel(const QString& text) {
  QLabel* label = new QLabel(text, this);
  label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  label->setWordWrap(true);
  label->setAlignment(Qt::AlignRight);
  layout_->addWidget(label);
  return label;
}

QPushButton* ConversationWindow::CreateFinishConversationButton() {
  QPushButton* button = new QPushButton("Finish", this);
  button->setObjectName("finish_button");
  layout_->addWidget(button, Qt::AlignCenter);
  connect(button, &QPushButton::pressed,
          this, [this]() {
            controller_->FinishConversation();
          });
  return button;
}

void ConversationWindow::keyPressEvent(QKeyEvent* event) {
  switch (event->key()) {
    case Qt::Key_1:
    case Qt::Key_2:
    case Qt::Key_3:
    case Qt::Key_4:
    case Qt::Key_5:
    case Qt::Key_6:
    case Qt::Key_7:
    case Qt::Key_8:
    case Qt::Key_9: {
      AnswerButtonPress(event->key() - Qt::Key_1);
      break;
    }
  }
}
