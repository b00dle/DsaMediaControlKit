#ifndef WEB_APP_CHAT_H
#define WEB_APP_CHAT_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>

namespace Web {
namespace App {

class Chat : public QWidget
{
    Q_OBJECT
public:
    explicit Chat(QWidget *parent = 0);

signals:

public slots:
private slots:
    void onReturnPressed();

private:
    void initWidgets();
    void initLayout();

    QTextEdit* text_edit_;
    QLineEdit* line_edit_;
};

} // namespace App
} // namespace Web

#endif // WEB_APP_CHAT_H
