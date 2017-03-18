#include "host.h"

#include <QHBoxLayout>
#include <QNetworkInterface>
#include <QHostAddress>

#include "resources/lib.h"

namespace Web {

Host::Host(QWidget *parent)
    : QDialog(parent)
    , listener_(0)
    , request_handler_(0)
    , line_edit_(0)
    , address_()
{
    initListener();
    initWidgets();
    initLayout();
}

Host::~Host()
{
    delete listener_;
    delete request_handler_;
    listener_ = 0;
    request_handler_ = 0;
}

const QString &Host::getAddress() const
{
    return address_;
}

void Host::initListener()
{
    QSettings* settings = new QSettings(
        Resources::Lib::WEB_CONFIG,
        QSettings::IniFormat,
        this
    );
    settings->beginGroup("listener");

    request_handler_ = new RequestHandler(this);

    listener_ = new stefanfrings::HttpListener(
        settings,
        request_handler_
    );
}

void Host::initWidgets()
{
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
             address_ = address.toString();
    }
    address_ = "http://" + address_ + ":8080";
    line_edit_ = new QLineEdit(address_, this);
    line_edit_->setReadOnly(true);
}

void Host::initLayout()
{
    setMinimumSize(200, 200);

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(line_edit_);

    setLayout(layout);
}

} // namespace Web
