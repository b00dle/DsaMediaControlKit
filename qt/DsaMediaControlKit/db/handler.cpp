#include "handler.h"

#include <QDebug>

namespace DB {

Handler::Handler(DB::Api* api, QObject *parent)
    : QObject(parent)
    , api_(api)
{
    if(api_ != 0) {
        QSqlTableModel* model = api_->getCategoryTable();

        for(int r = 0; r < model->rowCount(); ++r) {
            QString data_str = "";
            for(int c = 0; c < model->columnCount(); ++c) {
                if(c != 0)
                    data_str += " | ";
                data_str += model->data(model->index(r, c)).toString();
            }
            qDebug() << data_str;
        }
    }
}

void Handler::setApi(Api *api)
{
    api_ = api;
}

Api *Handler::getApi() const
{
    return api_;
}

void Handler::insertSoundFiles(const QList<DB::SoundFile>& sound_files)
{
    foreach(SoundFile sf, sound_files) {
        qDebug() << "==================";
        qDebug() << "info" << sf.getFileInfo().filePath();
        qDebug() << "category tree" << sf.getCategoryPath();
    }
}

} // namespace DB

