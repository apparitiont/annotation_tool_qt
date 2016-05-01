#include "donewdialog.h"
#include <QLayout>
#include <QTextStream>
#include <QChar>
#include <QString>
donewdialog::donewdialog(QWidget *parent) :
    QWidget(parent)
{
    model = new QFileSystemModel;
    tree = new QTreeView;
    index = new QModelIndex;
    connect(tree,SIGNAL(clicked(QModelIndex)),this,SLOT(displayImage(QModelIndex)));
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(tree);
    this->setBaseSize(50,500);
    this->setMaximumSize(200,500);
    this->setLayout(layout);
}
bool donewdialog::showFolder(QString &path)
{
    const QChar charTmp = '\\';
    const QString str("\\\\");
    path += "\\";

    path.replace(charTmp,str,Qt::CaseSensitive);

    *index = model->setRootPath(path);
    QTextStream out(stdout);
    out << path << endl;
    tree->setModel(model);
    tree->setRootIndex(model->index(path));

    // Demonstrating look and feel features
    tree->setAnimated(false);
    tree->setIndentation(20);
    tree->setSortingEnabled(false);
    tree->setColumnHidden(1,true);
    tree->setColumnHidden(2,true);
    tree->setColumnHidden(3,true);
    return 0;
}
void donewdialog::displayImage(QModelIndex idx)
{
    displayImageSingnal(idx);
}


donewdialog::~donewdialog()
{

}
