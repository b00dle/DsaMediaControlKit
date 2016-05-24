#include "handler.h"

#include <QDebug>

namespace DB {

Handler::Handler(DB::Api* api, QObject *parent)
    : QObject(parent)
    , api_(api)
    , sound_file_model_(0)
    , category_tree_model_(0)
{
    if(api_ != 0) {
        category_tree_model_ = new Model::CategoryTreeModel(this, api_->getCategoryTable());
        sound_file_model_ = api_->getSoundFileTable();
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

void Handler::addSoundFile(const QFileInfo& info)
{
    api_->insertSoundFile(info);
}

void Handler::addCategory(QString name, CategoryRecord *parent)
{
    int p_id = -1;
    if(parent != 0)
        p_id = parent->id;
    api_->insertCategory(name, p_id);
    category_tree_model_->update();
}

void Handler::insertSoundFilesAndCategories(const QList<DB::SoundFile>& sound_files)
{
    if(category_tree_model_ == 0)
        category_tree_model_ = new Model::CategoryTreeModel(this, api_->getCategoryTable());

    CategoryRecord* cat = 0;
    foreach(SoundFile sf, sound_files) {
        if(api_->soundFileExists(sf.getFileInfo().filePath(), sf.getFileInfo().fileName()))
            continue;

        qDebug() << "=========IMPORTING=========";
        qDebug() << "info" << sf.getFileInfo().filePath();
        qDebug() << "category tree" << sf.getCategoryPath();

        addSoundFile(sf.getFileInfo());
        cat = category_tree_model_->getCategoryByPath(sf.getCategoryPath());
        if(cat == 0) {
            addCategory(sf.getCategoryPath());
            cat = category_tree_model_->getCategoryByPath(sf.getCategoryPath());
        }
        qDebug() << cat->name << cat->id;

        // TODO insert sound_file category
    }
    qDebug() << "DONE.";
}

void Handler::addCategory(const QStringList &path)
{
    CategoryRecord* parent = 0;
    int j = 0;
    for(int i = 0; i < path.size(); ++i) {
        CategoryRecord* cat = category_tree_model_->getCategoryByPath(path.mid(0,i+1));
        if(cat == 0) {
            j = i;
            break;
        }
        parent = cat;
    }

    while(j < path.size()) {
        addCategory(path[j], parent);
        parent = category_tree_model_->getCategoryByPath(path.mid(0,j+1));
        ++j;
    }
}

} // namespace DB

