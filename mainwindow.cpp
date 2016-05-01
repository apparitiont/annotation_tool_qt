#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>
#include "paintWidget.h"
#include "donewdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)

{
    aboutInfo = new QMessageBox;
    helpMessage = "use Ctrl+Alt+A to annotation \r\n use right-click to cancel the selection and use double-click to specifiy the selection \r\n designed by dt";

    aboutInfo->setText(helpMessage);
    menuBar = new QMenuBar;
    menu1 = new QMenu(tr("file"));
    menu2 = new QMenu(tr("help"));
    openFolder = new QAction(tr("openfloder"),this);
    quit = new QAction(tr("quit"),this);
    about = new QAction(tr("about"),this);
    fileShow = new donewdialog;
    paintScrollArea = new QScrollArea;
    painterWidget = new paintWidget;
    connect(openFolder,SIGNAL(triggered()),this,SLOT(openFileDialog()));
    connect(quit,SIGNAL(triggered(bool)),this,SLOT(close()));
    connect(about,SIGNAL(triggered(bool)),aboutInfo,SLOT(show()));
    connect(fileShow,SIGNAL(displayImageSingnal(QModelIndex)),painterWidget,SLOT(showNewPicture(QModelIndex)));
    connect(this,SIGNAL(transferWorkingDictory(QString &)),painterWidget,SLOT(setWorkingDictory(QString &)));
    connect(this,SIGNAL(paintKeyEvent(QKeyEvent *)),painterWidget,SLOT(paintKeyEvent(QKeyEvent*)));

    menu1->addAction(openFolder);
    //menu1->addAction(save);
    menu1->addAction(quit);
    menu2->addAction(about);
    menuBar->addMenu(menu1);
    menuBar->addMenu(menu2);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(fileShow);
    paintScrollArea->setWidget(painterWidget);
    layout->addWidget(paintScrollArea);
    paintScrollArea->setWidgetResizable(true);
    this->setMenuBar(menuBar);
    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    this->setCentralWidget(widget);
    this->setMinimumSize(700,500);

    setFocusPolicy(Qt::StrongFocus);


}
void MainWindow::openFileDialog()
{
    QString dir;
    dir = fileDialog->getExistingDirectory(this,tr("select dir"),"",QFileDialog::ShowDirsOnly);

    if(!dir.isEmpty())
    {
        transferWorkingDictory(dir);
        if(!fileShow->showFolder(dir))
            return;
    }

}
void MainWindow::displayImage(QModelIndex idx)
{
     QString selectedTexts;
     selectedTexts = idx.data(Qt::DisplayRole).toString();
     if(!painterWidget->openImage(selectedTexts))
     {
         QMessageBox::critical(NULL, "提示", "无法创建文件");
     }
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    paintKeyEvent(event);
}
MainWindow::~MainWindow()
{

}

