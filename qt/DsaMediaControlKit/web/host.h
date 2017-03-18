#ifndef WEB_HOST_H
#define WEB_HOST_H

#include <QDialog>
#include <QLabel>

namespace Web {

class Host : public QDialog
{
    Q_OBJECT
public:
    explicit Host(QWidget *parent = 0);

signals:

public slots:

private:
    void initWidgets();
    void initLayout();

    QLabel* label_;
};

} // namespace Web
#endif // HOST_H
