#ifndef WEB_PRESET_CONTROLLER_HANDLER_H
#define WEB_PRESET_CONTROLLER_HANDLER_H

#include "httprequesthandler.h"
#include "2D/graphics_view.h"

namespace Web {

class PresetController : public stefanfrings::HttpRequestHandler {
    Q_OBJECT
public:
    PresetController(QObject* parent=0);
    void service(stefanfrings::HttpRequest& request, stefanfrings::HttpResponse& response);

    void setPresetView(TwoD::GraphicsView* preset_view);
private:
    TwoD::GraphicsView* preset_view_;
};

} // namespace Web

#endif // WEB_PRESET_CONTROLLER_HANDLER_H
