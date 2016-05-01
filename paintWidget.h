#ifndef PAINTWDGET_H
#define PAINTWDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QModelIndex>
#include <QString>
#include <QTextStream>
#include <QFile>
#include <QIODevice>
#include <QFileInfo>
#include <QEvent>
#include <QTimer>

#include<QPainter>
#include<QPrintDialog>
#include<QPrinter>
#include<QCursorShape>


class paintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit paintWidget(QWidget *parent = 0);
    ~paintWidget();
    bool openImage(QString &fileName);//打开图片
    bool saveImage(const QString &fileName,const char *fileFormat);
    QSize getImageSize();

    //工具
    void zoomIn();//放大
    void zoomOut();//缩小

    //框的图形
    enum shapeType
    {
        Rectanggle
    };

    void setShape(shapeType shape);

protected:
    void paintEvent(QPaintEvent *);//重绘事件


    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *event);
    void paint(QImage &theimage);
    void setImageSize(int width,int height);
    void wheelEvent(QWheelEvent *);

private:
    QString fileName;
    QString workingDictory;
    QString fileContent;
    QStringList fileContentList;
    QFileInfo info;
    QFile file;
    QFile fileOut;
    QColor backColor;
    QImage image;//用于在其上绘图
    QImage imageAlpha;
    QImage tempImage;
    QPoint lastPoint,endPoint,tempPoint1,tempPoint2;
    bool modified;
    qreal scale;
    qreal wheelCounter;
    qreal shear;
    QBrush brushColor;
    shapeType curShape;
    QColor penColor;
    bool isDrawing;
    Qt::PenStyle penStyle;
    int penWidth;
    int imageNumber;
    QSize imageSize;
    qreal zoom;
    QTimer timer;


signals:

public slots:
    void showNewPicture(QModelIndex);
    void setWorkingDictory(QString &);
    void paintKeyEvent(QKeyEvent *);

};

#endif // PAINTWDGET_H
