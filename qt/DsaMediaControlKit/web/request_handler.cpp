#include "request_handler.h"

#include <QDebug>
#include <QByteArray>

#include "resources/lib.h"

namespace Web {

RequestHandler::RequestHandler(QObject* parent)
    : stefanfrings::HttpRequestHandler(parent)
    , preset_controller_(0)
{
    preset_controller_ = new PresetController(this);
}

void RequestHandler::service(stefanfrings::HttpRequest &request, stefanfrings::HttpResponse &response)
{
    QString path(request.getPath());
    if (path.compare("/preset") == 0) {
        preset_controller_->service(request, response);
    } else if(path.compare("/") == 0) {
        QByteArray index = Resources::Lib::WEB_INDEX.toStdString().c_str();
        response.write(index, true);
    } else {
        response.write("NOT FOUND",true);
    }
}

void RequestHandler::setPresetView(TwoD::GraphicsView *preset_view)
{
    preset_controller_->setPresetView(preset_view);
}

} // namespace Web
