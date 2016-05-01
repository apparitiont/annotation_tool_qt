#ifndef DONEWDIALOG_H
#define DONEWDIALOG_H

#include <QWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QModelIndex>

class donewdialog : public QWidget
{
    Q_OBJECT
public:
    explicit donewdialog(QWidget *parent = 0);
    ~donewdialog();
public slots:
    bool showFolder(QString &path);

private:
    QFileSystemModel *model;
    QTreeView *tree;
    QModelIndex *index;

signals:
    void displayImageSingnal(QModelIndex);
public slots:
    void displayImage(QModelIndex);

};

#endif // DONEWDIALOG_H
