#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QFileDialog>
#include <QDialog>
#include <QLabel>
#include <QMessageBox>
#include <QString>
#include <QModelIndex>
#include <QScrollArea>

class paintWidget;
class donewdialog;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private:
    QMenu *menu1;
    QMenu *menu2;
    QMenuBar *menuBar;
    QAction *openFolder;
    QAction *quit;
    QAction *about;
    //QAction *save;
    QFileDialog *fileDialog;
    QMessageBox *aboutInfo;
    paintWidget *painterWidget;
    donewdialog *fileShow;
    QScrollArea *paintScrollArea;
    QString helpMessage;
protected:
    void keyPressEvent(QKeyEvent *);

private slots:
    void openFileDialog();
    void displayImage(QModelIndex idx);
signals:
    void transferWorkingDictory(QString &);
    void paintKeyEvent(QKeyEvent *event);

};

#endif // MAINWINDOW_H
