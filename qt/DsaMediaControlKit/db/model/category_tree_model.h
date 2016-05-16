#ifndef DB_MODEL_CATEGORY_TREE_MODEL_H
#define DB_MODEL_CATEGORY_TREE_MODEL_H

#include <QStandardItemModel>
#include <QSqlRelationalTableModel>

#include "db/tables.h"

namespace DB {
namespace Model {

/*
 * Class derived from QStandartItemModel
 * contains an instance of QSqlRelationalTableModel
 * which refers to a hierarchical category db table.
 * This class will recursively transfer given table into
 * an n-dimensional QStandardItemModel, which can be connected
 * to a QTreeView. Convinience functions ease data access.
*/

class CategoryTreeModel : public QStandardItemModel
{
    Q_OBJECT
public:
    CategoryTreeModel(QObject* parent = 0, QSqlRelationalTableModel* category_table = 0);

    void setCategoryTableModel(QSqlRelationalTableModel* category_table);
    void setEditable(bool);

    Qt::ItemFlags flags(const QModelIndex &index) const;

    CategoryRecord* getCategoryByItem(QStandardItem*);
    CategoryRecord* getCategoryByPath(QStringList const&);
    CategoryRecord* getCategoryByRid(int);
    QStandardItem* getItemByCategory(CategoryRecord*);
    QStandardItem* getItemByPath(QStringList const&);
    QStringList const getSubCategoryNamesByItem(QStandardItem* item = 0);
    QStringList const getSubCategoryNamesByCategory(CategoryRecord*);

    static bool equalCategoryName(QString const& left, QString const& right);
    bool exists(QString const& name, CategoryRecord* parent);

public slots:
    void update();
    void dbRowsInserted(QModelIndex,int, int);
    void onDataChanged(QModelIndex const& topLeft,
                       QModelIndex const& bottomRight,
                       QVector<int> const& roles);

signals:
    void updated();

private:
    void createModel();
    void setChildItems(QStandardItem* item, QList<CategoryRecord*> children);

    QSqlRelationalTableModel* table_model_;

    QMap<int, CategoryRecord*> categories_;
    QMap<CategoryRecord*, QStandardItem*> category_to_item_;

    bool editable_;
};

} // namespace Model
} // namespace DB
#endif // DB_MODEL_CATEGORY_TREE_MODEL_H
