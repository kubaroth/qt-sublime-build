#include <QApplication>
#include <QtGui>
#include <QSplitter>
#include <QDirModel>
#include <QTreeView>
#include <QListView>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(simpletreemodel);

    QApplication app(argc, argv);
    QSplitter *splitter = new QSplitter;
    QDirModel *model = new QDirModel;
     
    auto dirpath = QString("%1/temp/new_folder1").arg(QDir::homePath());
    /// create two views:
    QTreeView *tree = new QTreeView(splitter);
    tree->setModel(model);
    tree->setRootIndex(model->index(dirpath ));

    splitter->setWindowTitle("Two views onto the same file system model");
    splitter->show();

    // convention used when dealing with Model Indexes
    QModelIndex parentIndex = model->index(dirpath);
    int numRows = model->rowCount(parentIndex);
    qDebug() << numRows;
    
    //obtain data from a model
    for (int row=0; row<numRows; ++row ){
        QModelIndex index=model->index(row,0, parentIndex);
        QString text = model->data(index, Qt::DisplayRole).toString();
        tree->setRowHidden(1,parentIndex,true);
        qDebug() << text;
     }
    return app.exec();
}
