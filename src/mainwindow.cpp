#include "mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    Q_INIT_RESOURCE(simpletreemodel);

    model = new QStandardItemModel;

    /// create widgets:
    QSplitter *splitter = new QSplitter();
    treeview = new QTreeView(splitter);
    QLineEdit *lineedit = new QLineEdit(splitter);
    keyEnterReceiver *keyPressEater = new keyEnterReceiver(); // enable press Enter shortcut

    /// Set attrbutes
    this->setCentralWidget(splitter);  // fit the size of the spliter into the main window
    treeview->setModel(model);
    // treeview->installEventFilter(keyPressEater);
    lineedit->installEventFilter(keyPressEater);

    splitter->setWindowTitle("Example");
    splitter->setOrientation(Qt::Vertical);
    // FIXME: - fixed hight of linedit
    //        - make it appear on ctrl-F

    // connect(exitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
    connect(lineedit, &QLineEdit::textChanged, this, &MainWindow::hello);
    connect(lineedit, &QLineEdit::textChanged, this, &MainWindow::search);



    /// Add items to a tree 
    QList<QString> names = {"aaa", "aac", "bbb", "ccc"};

    for (auto name : names){
        Block b = {1, 2.0, name};
        QVariant var1;
        var1.setValue(b);
        auto item = new QStandardItem(b.name);
        item->setData(var1);
        model->appendRow(item);
    }   


    // parents.last()->appendChild(new TreeItem(columnData, parents.last()));

    treeview->setDragDropMode(QAbstractItemView::InternalMove);
    treeview->setSelectionMode(QAbstractItemView::ExtendedSelection);
    treeview->setDragEnabled(true);
    treeview->setAcceptDrops(true);
    treeview->setDropIndicatorShown(true);

}

void MainWindow::search(const QString inputtext) const {
    qDebug() << "search: "<< inputtext;

    QRegularExpression re(inputtext);

    // convention used when dealing with Model Indexes
    QStandardItem  *parentItem = model->invisibleRootItem();
    QModelIndex  parentIndex = parentItem->index();
    int numRows = model->rowCount(parentIndex);
    qDebug() << numRows;

    treeview->setRowHidden(1,parentIndex,true);

    //obtain data from a model
    for (int row=0; row<numRows; ++row ){
        if (inputtext == ""){
            treeview->setRowHidden(row,parentIndex,false);
            continue;
        }
        QModelIndex index=model->index(row,0, parentIndex);
        QString itemtext = model->data(index, Qt::DisplayRole).toString();
        QRegularExpressionMatch match = re.match(itemtext, 0, QRegularExpression::PartialPreferFirstMatch);
        if (match.hasMatch()){
            // qDebug() << "found" << inputtext;
            treeview->setRowHidden(row,parentIndex,false);
        }
        else{
            treeview->setRowHidden(row,parentIndex,true);
        }
     }

}


////// Reference:

// void MainWindow::insertChild()
// {
//     QModelIndex index = view->selectionModel()->currentIndex();
//     QAbstractItemModel *model = view->model();

//     if (model->columnCount(index) == 0) {
//         if (!model->insertColumn(0, index))
//             return;
//     }

//     if (!model->insertRow(0, index))
//         return;

//     for (int column = 0; column < model->columnCount(index); ++column) {
//         QModelIndex child = model->index(0, column, index);
//         model->setData(child, QVariant("[No data]"), Qt::EditRole);
//         if (!model->headerData(column, Qt::Horizontal).isValid())
//             model->setHeaderData(column, Qt::Horizontal, QVariant("[No header]"), Qt::EditRole);
//     }

//     view->selectionModel()->setCurrentIndex(model->index(0, 0, index),
//                                             QItemSelectionModel::ClearAndSelect);
//     updateActions();
// }

// bool MainWindow::insertColumn()
// {
//     QAbstractItemModel *model = view->model();
//     int column = view->selectionModel()->currentIndex().column();

//     // Insert a column in the parent item.
//     bool changed = model->insertColumn(column + 1);
//     if (changed)
//         model->setHeaderData(column + 1, Qt::Horizontal, QVariant("[No header]"), Qt::EditRole);

//     updateActions();

//     return changed;
// }

// void MainWindow::insertRow()
// {
//     QModelIndex index = view->selectionModel()->currentIndex();
//     QAbstractItemModel *model = view->model();

//     if (!model->insertRow(index.row()+1, index.parent()))
//         return;

//     updateActions();

//     for (int column = 0; column < model->columnCount(index.parent()); ++column) {
//         QModelIndex child = model->index(index.row()+1, column, index.parent());
//         model->setData(child, QVariant("[No data]"), Qt::EditRole);
//     }
// }

// bool MainWindow::removeColumn()
// {
//     QAbstractItemModel *model = view->model();
//     int column = view->selectionModel()->currentIndex().column();

//     // Insert columns in each child of the parent item.
//     bool changed = model->removeColumn(column);

//     if (changed)
//         updateActions();

//     return changed;
// }

// void MainWindow::removeRow()
// {
//     QModelIndex index = view->selectionModel()->currentIndex();
//     QAbstractItemModel *model = view->model();
//     if (model->removeRow(index.row(), index.parent()))
//         updateActions();
// }

// void MainWindow::updateActions()
// {
//     bool hasSelection = !view->selectionModel()->selection().isEmpty();
//     removeRowAction->setEnabled(hasSelection);
//     removeColumnAction->setEnabled(hasSelection);

//     bool hasCurrent = view->selectionModel()->currentIndex().isValid();
//     insertRowAction->setEnabled(hasCurrent);
//     insertColumnAction->setEnabled(hasCurrent);

//     if (hasCurrent) {
//         view->closePersistentEditor(view->selectionModel()->currentIndex());

//         int row = view->selectionModel()->currentIndex().row();
//         int column = view->selectionModel()->currentIndex().column();
//         if (view->selectionModel()->currentIndex().parent().isValid())
//             statusBar()->showMessage(tr("Position: (%1,%2)").arg(row).arg(column));
//         else
//             statusBar()->showMessage(tr("Position: (%1,%2) in top level").arg(row).arg(column));
//     }
// }