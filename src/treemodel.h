#pragma once

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QStringList>
#include <QtGui>

class TreeItem;

class TreeModel : public QAbstractItemModel{
    Q_OBJECT
    
public:
    TreeModel(const QStringList &headers, const QString &data,
              QObject *parent = 0);
    ~TreeModel();
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    // Editable mode
    // flag should return ItemIsEditable 
    // The dataChanged() and headerDataChanged() signals must be emitted 
    // explicitly when reimplementing the setData() and 
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    bool setHeaderData(int section, Qt::Orientation orientation,
                       const QVariant &value, int role = Qt::EditRole) override; 
    bool insertColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex())  override;
    bool removeColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex()) override;
    bool insertRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) override;
    
    
private:
    void setupModelData(const QStringList &lines, TreeItem *parent);
    TreeItem *getItem(const QModelIndex &index) const;
    TreeItem *rootItem;
};


class keyEnterReceiver : public QObject
{
    Q_OBJECT
public:
    keyEnterReceiver(QWidget * parent=0){}
protected:
    bool eventFilter(QObject* obj, QEvent* event){
    if (event->type()==QEvent::KeyPress) {        
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        if ( (key->key()==Qt::Key_Enter) || (key->key()==Qt::Key_Return) ) {
            //Enter or return was pressed
            qDebug()<< "Enter pressed++++ "<< obj ;
        } else {
            return QObject::eventFilter(obj, event);
        }
        return true;
    } else {
        return QObject::eventFilter(obj, event);
    }
    return false;
}
};