#ifndef WEB_RESPONSE_H
#define WEB_RESPONSE_H

#include <QString>
#include <QJsonObject>
#include <QJsonDocument>

namespace Web {

/**
 * data transfer object for server response messages
*/

struct Response {
    QString err;
    QJsonValue return_value;
    QString func;

    Response(const QString& e="", const QJsonValue& r="", const QString& f="")
        : err(e)
        , return_value(r)
        , func(f)
    {}

    const QJsonObject toJsonObject() {
        QJsonObject obj;
        obj["err"] = err;
        obj["return"] = return_value;
        obj["func"] = func;
        return obj;
    }

    const QString toJson() {
        QJsonDocument doc;
        doc.setObject(toJsonObject());
        return doc.toJson();
    }

    const QByteArray toByteArray() {
        return QByteArray(toJson().toStdString().c_str());
    }
};

}

#endif // RESPONSE_H
