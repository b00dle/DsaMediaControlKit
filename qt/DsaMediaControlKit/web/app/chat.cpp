#include "chat.h"

#include <QHBoxLayout>

namespace Web {
namespace App {

Chat::Chat(QWidget *parent)
    : QWidget(parent)
    , text_edit_(0)
    , line_edit_(0)
{
    initWidgets();
    initLayout();
}

void Chat::onReturnPressed()
{
    text_edit_->moveCursor(QTextCursor::End);
    text_edit_->insertPlainText(line_edit_->text() + "\n");
    line_edit_->clear();
}

void Chat::initWidgets()
{
    text_edit_ = new QTextEdit(this);
    text_edit_->setReadOnly(true);

    line_edit_ = new QLineEdit(this);

    connect(line_edit_, SIGNAL(returnPressed()),
            this, SLOT(onReturnPressed()));
}

void Chat::initLayout()
{
    QVBoxLayout* layout = new QVBoxLayout;

    layout->addWidget(text_edit_, 10);
    layout->addWidget(line_edit_, 0);

    setLayout(layout);
}

} // namespace App
} // namespace Web
