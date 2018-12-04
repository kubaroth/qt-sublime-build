#pragma once

#include <QMainWindow>
#include <QModelIndex>
#include <QtGui>
#include <QSplitter>
#include <QStandardItemModel>
#include <QTreeView>
#include <QListView>
#include <QLineEdit>
#include <QFile>


#include <QVariant>
#include <QMetaType>


struct Block{
    int x;
    float y;
    QString name;
};
Q_DECLARE_METATYPE(Block);


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    
    void hello(){ qDebug()<< "hello";}
    void search(const QString) const;

// public slots:
//     void updateActions();

// private slots:
//     void insertChild();
//     bool insertColumn();
//     void insertRow();
//     bool removeColumn();
//     void removeRow();

private:
	QStandardItemModel *model;
	QTreeView *treeview;
	QString dirpath;
    
    
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