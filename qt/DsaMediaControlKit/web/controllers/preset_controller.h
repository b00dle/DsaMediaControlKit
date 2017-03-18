#ifndef WEB_PRESET_CONTROLLER_HANDLER_H
#define WEB_PRESET_CONTROLLER_HANDLER_H

#include "httprequesthandler.h"

namespace Web {

class PresetController : public stefanfrings::HttpRequestHandler {
    Q_OBJECT
public:
    PresetController(QObject* parent=0);
    void service(stefanfrings::HttpRequest& request, stefanfrings::HttpResponse& response);
};

} // namespace Web

#endif // WEB_PRESET_CONTROLLER_HANDLER_H
