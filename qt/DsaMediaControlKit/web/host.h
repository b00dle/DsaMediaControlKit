#ifndef WEB_HOST_H
#define WEB_HOST_H

#include <QDialog>
#include <QLineEdit>

#include "httplistener.h"
#include "request_handler.h"

namespace Web {

class Host : public QDialog
{
    Q_OBJECT
public:
    explicit Host(QWidget *parent = 0);
    ~Host();

    QString const& getAddress() const;
signals:

public slots:

private:
    void initListener();
    void initWidgets();
    void initLayout();

    // Start the HTTP server
    stefanfrings::HttpListener* listener_;
    RequestHandler* request_handler_;
    QString address_;

    QLineEdit* line_edit_;
};

} // namespace Web
#endif // HOST_H
