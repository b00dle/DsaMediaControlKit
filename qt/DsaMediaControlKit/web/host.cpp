#include "host.h"

#include <QHBoxLayout>
#include <QNetworkInterface>
#include <QHostAddress>
#include <QRegExp>

#include "resources/lib.h"

namespace Web {

Host::Host(QWidget *parent)
    : QDialog(parent)
    , listener_(0)
    , request_handler_(0)
    , address_()
    , line_edit_(0)
    , chat_app_(0)
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

void Host::setPresetView(TwoD::GraphicsView *preset_view)
{
    request_handler_->setPresetView(preset_view);
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
    address_ = "http://" + address_ + ":8080/";
    Resources::Lib::WEB_INDEX.replace(
        QRegExp::escape("KOT_BRO_SHIT"),
        QRegExp::escape("http://192.168.1.108:8080/")
    );
    qDebug() << address_;
    line_edit_ = new QLineEdit(address_, this);
    line_edit_->setReadOnly(true);

    chat_app_ = new App::Chat(this);
}

void Host::initLayout()
{
    setMinimumSize(400, 200);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(line_edit_, 0);
    layout->addWidget(chat_app_, 10);

    setLayout(layout);
}

} // namespace Web
