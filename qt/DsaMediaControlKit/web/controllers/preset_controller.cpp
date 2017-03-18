#include "preset_controller.h"

#include <QDebug>

namespace Web {

PresetController::PresetController(QObject* parent)
    : stefanfrings::HttpRequestHandler(parent)
{
    // empty
}

void PresetController::service(stefanfrings::HttpRequest &request, stefanfrings::HttpResponse &response)
{
    response.write("PENIS",true);
}

} // namespace Web
