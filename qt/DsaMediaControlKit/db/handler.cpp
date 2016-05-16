#include "handler.h"

#include <QDebug>

namespace DB {

Handler::Handler(DB::Api* api, QObject *parent)
    : QObject(parent)
    , api_(api)
    , category_tree_model_(0)
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

Model::CategoryTreeModel *Handler::getCategoryTreeModel()
{
    if(category_tree_model_ == 0)
        category_tree_model_ = new Model::CategoryTreeModel(this, api_->getCategoryTable());

    return category_tree_model_;
}

void Handler::addCategory(QString name, CategoryRecord *parent)
{
    int p_id = -1;
    if(parent != 0)
        p_id = parent->id;
    api_->insertCategory(name, p_id);
}

void Handler::insertSoundFiles(const QList<DB::SoundFile>& sound_files)
{
    if(category_tree_model_ == 0)
        category_tree_model_ = new Model::CategoryTreeModel(this, api_->getCategoryTable());

    CategoryRecord* cat = 0;
    foreach(SoundFile sf, sound_files) {
        qDebug() << "==================";
        qDebug() << "info" << sf.getFileInfo().filePath();
        qDebug() << "category tree" << sf.getCategoryPath();
        cat = category_tree_model_->getCategoryByPath(sf.getCategoryPath());
        if(cat == 0)
            addCategory(sf.getCategoryPath());
    }
}

void Handler::addCategory(const QStringList &path)
{
    CategoryRecord* parent = 0;
    int j = 0;
    for(int i = 0; i < path.size(); ++i) {
        CategoryRecord* cat = category_tree_model_->getCategoryByPath(path.mid(0,i+1));
        if(cat != 0)
            break;
        parent = cat;
    }

    while(j < path.size()) {
        addCategory(path[j], parent);
        category_tree_model_->update();
        parent = category_tree_model_->getCategoryByPath(path.mid(0,j+1));
        ++j;
    }
}

} // namespace DB

