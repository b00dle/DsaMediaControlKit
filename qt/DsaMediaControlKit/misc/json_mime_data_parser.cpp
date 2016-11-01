#include "json_mime_data_parser.h"

#include <QJsonArray>

namespace Misc {

JsonMimeDataParser::JsonMimeDataParser()
{}

QMimeData* JsonMimeDataParser::toJsonMimeData(DB::TableRecord* rec)
{
    QMimeData* data = 0;
    if(rec == 0)
        return data;

    QJsonObject obj(toJsonObject(rec));
    if(obj.isEmpty())
        return data;

    QJsonDocument doc(obj);

    data = new QMimeData;
    data->setText(QString(doc.toJson()));

    return data;
}

QMimeData *JsonMimeDataParser::toJsonMimeData(const QList<DB::TableRecord *>& records)
{
    QMimeData* data = 0;
    if(records.size() == 0)
        return data;

    QJsonArray arr;
    foreach(DB::TableRecord* rec, records) {
        QJsonObject obj(toJsonObject(rec));
        if(obj.isEmpty())
            continue;
        arr.append(obj);
    }

    QJsonDocument doc(arr);

    data = new QMimeData;
    data->setText(QString(doc.toJson()));

    return data;
}

DB::TableRecord *JsonMimeDataParser::toTableRecord(const QMimeData* mime)
{
    if(mime == 0 || !mime->hasText())
        return 0;

    QJsonDocument doc = QJsonDocument::fromJson(mime->text().toUtf8());
    if(doc.isNull() || doc.isEmpty() || !doc.isObject())
        return 0;

    return toTableRecord(doc.object());
}

QList<DB::TableRecord *> JsonMimeDataParser::toTableRecordList(const QMimeData* mime)
{
    QList<DB::TableRecord*> records;
    if(mime == 0 || !mime->hasText())
        return records;

    QJsonDocument doc = QJsonDocument::fromJson(mime->text().toUtf8());
    if(doc.isNull() || doc.isEmpty())
        return records;

    if(doc.isObject()) {
        DB::TableRecord* rec = toTableRecord(mime);
        if(rec == 0)
            return records;
        records.append(rec);
    }
    else if(doc.isArray()) {
        foreach(QJsonValue val, doc.array()) {
            if(!val.isObject())
                continue;

            DB::TableRecord* rec = toTableRecord(val.toObject());
            if(rec == 0)
                continue;
            records.append(rec);
        }
    }

    return records;
}

DB::TableRecord *JsonMimeDataParser::toTableRecord(const QJsonObject& obj)
{
    DB::TableRecord* rec = 0;

    if(!obj.contains("type"))
        return rec;

    if(obj["type"] == DB::SOUND_FILE) {
        int id = -1;
        QString name = "";
        QString path = "";
        if(obj.contains("id"))
            id = obj["id"].toInt();
        if(obj.contains("name") || obj["name"].isString())
            name = obj["name"].toString();
        if(obj.contains("path") || obj["path"].isString())
            path = obj["path"].toString();

        rec = new DB::SoundFileRecord(id, name, path);
    }
    else if(obj["type"] == DB::CATEGORY) {
        int id = -1;
        QString name = "";
        int parent_id = -1;
        if(obj.contains("id"))
            id = obj["id"].toInt();
        if(obj.contains("name") || obj["name"].isString())
            name = obj["name"].toString();
        if(obj.contains("parent_id"))
            parent_id = obj["parent_id"].toInt();

        rec = new DB::CategoryRecord(id, name, parent_id);
    }

    return rec;
}

const QJsonObject JsonMimeDataParser::toJsonObject(DB::TableRecord* rec)
{
    QJsonObject obj;

    if(rec == 0)
        return obj;

    switch(rec->index) {
        case DB::SOUND_FILE:
            obj = toJsonObject((DB::SoundFileRecord*) rec);
            break;

        case DB::CATEGORY:
            obj = toJsonObject((DB::CategoryRecord*) rec);
            break;

        case DB::SOUND_FILE_CATEGORY:
        case DB::NONE:
        default:
            break;
    }

    return obj;
}

const QJsonObject JsonMimeDataParser::toJsonObject(DB::SoundFileRecord* rec)
{
    QJsonObject obj;

    if(rec == 0)
        return obj;

    obj.insert("type", QJsonValue(rec->index));
    obj.insert("id", QJsonValue(rec->id));
    obj.insert("name", QJsonValue(rec->name));
    obj.insert("path", QJsonValue(rec->path));

    return obj;
}

const QJsonObject JsonMimeDataParser::toJsonObject(DB::CategoryRecord* rec)
{
    QJsonObject obj;

    if(rec == 0)
        return obj;

    obj.insert("type", QJsonValue(rec->index));
    obj.insert("id", QJsonValue(rec->id));
    obj.insert("name", QJsonValue(rec->name));
    obj.insert("parent_id", QJsonValue(rec->parent_id));

    return obj;
}

} // namespace Misc
