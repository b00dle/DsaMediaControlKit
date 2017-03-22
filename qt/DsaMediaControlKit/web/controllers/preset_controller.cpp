#include "preset_controller.h"

#include <QDebug>
#include <QList>
#include <QMultiMap>
#include <QJsonDocument>
#include <QJsonArray>
#include <QUuid>

#include "web/response.h"

namespace Web {

PresetController::PresetController(QObject* parent)
    : stefanfrings::HttpRequestHandler(parent)
    , preset_view_(0)
{}

void PresetController::service(stefanfrings::HttpRequest &request, stefanfrings::HttpResponse &response)
{
    if(preset_view_ == 0)
        response.write("Failure: No preset view set on server.", true);

    QMultiMap<QByteArray,QByteArray> parameters = request.getParameterMap();

    if(parameters.size() == 0) {
        QJsonDocument doc;
        doc.setObject(preset_view_->toJsonObject());
        response.write(doc.toJson(), true);
    } else if(parameters.contains("play")) {
        QByteArray play_what = parameters.value("play");
        QUuid tile_uuid = QUuid(QString(play_what));
        QJsonArray arr;
        arr.append(QString(play_what));
        arr.append(preset_view_->activate(tile_uuid));
        Response r("", QJsonValue(arr), "play");
        response.write(r.toByteArray(), true);
    } else if(parameters.contains("stop")) {
        QByteArray stop_what = parameters.value("stop");
        QUuid tile_uuid = QUuid(QString(stop_what));
        QJsonArray arr;
        arr.append(QString(stop_what));
        arr.append(preset_view_->deactivate(tile_uuid));
        Response r("", QJsonValue(arr), "stop");
        response.write(r.toByteArray(), true);
    } else if(parameters.contains("is_playing")) {
        QByteArray is_playing_what = parameters.value("is_playing");
        QUuid tile_uuid = QUuid(QString(is_playing_what));
        QJsonArray arr;
        arr.append(QString(is_playing_what));
        arr.append(preset_view_->isActivated(tile_uuid));
        Response r("", QJsonValue(arr), "is_activated");
        response.write(r.toByteArray(), true);
    }
    else {
        Response r("request not implemented", "", "");
        response.write(r.toByteArray(), true);
    }
    /*
    QString path(request.getPath());
    if (path.compare("/preset") == 0)
        preset_controller_->service(request, response);
    else
        response.write("NOT FOUND",true);*/
}

void PresetController::setPresetView(TwoD::GraphicsView *preset_view)
{
    preset_view_ = preset_view;
}

} // namespace Web
