#pragma once


#include <QList>
#include <QVariant>
#include <QStringList>
#include <QVector>

class TreeItem{
public:
    explicit TreeItem(const QVector<QVariant> &data, TreeItem *parent = 0);
    ~TreeItem();

    TreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    // editable
    bool insertChildren(int position, int count, int columns);
    bool insertColumns(int position, int columns);
    TreeItem *parent();
    bool removeChildren(int position, int count);
    bool removeColumns(int position, int columns);
    int childNumber() const;
    bool setData(int column, const QVariant &value);

private:
    QList<TreeItem*> m_childItems; // stores all children - used for cleanup
    QVector<QVariant> m_itemData;
    TreeItem *m_parentItem;
};
