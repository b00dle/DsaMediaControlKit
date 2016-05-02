#include "sqlite_wrapper.h"

#include <QDebug>

namespace DB {

SqliteWrapper::SqliteWrapper(QString const& db_path, QObject* parent):
    QObject(parent)
  , db_()
{
    initDB(db_path);
}

QSqlTableModel* SqliteWrapper::getTable(TableIndex index)
{
    if(!db_.isOpen() || index == NONE) {
        qDebug() << "FAILURE: database not open";
        return 0;
    }
    else {
        QSqlTableModel* model = new QSqlTableModel(this);
        model->setTable(toString(index));
        model->select();
        return model;
    }
}

void SqliteWrapper::open()
{
    if(db_.isOpen()) {
        qDebug() << "NOTIFICATION: database is already open";
        return;
    }

    if(db_.open()) {
        qDebug() << "SUCCESS: connected to database";
    }
    else {
        qDebug() << "FAILURE: could not open database";
    }
}

void SqliteWrapper::close()
{
    if(db_.isOpen()) {
        db_.close();
    }
    else {
        qDebug() << "NOTIFICATION: database is not open";
    }
}

void SqliteWrapper::initDB(QString const& db_path)
{
    db_ = QSqlDatabase::addDatabase("QSQLITE");
    db_.setDatabaseName(db_path);

    open();
}

}
