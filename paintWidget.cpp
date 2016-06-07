#include <paintWidget.h>
#include <stdio.h>
#include <math.h>
#include <QDebug>
#include <QMessageBox>
#include <QRegExp>

paintWidget::paintWidget(QWidget *parent) :
    QWidget(parent)
{
    image=QImage(500,500,QImage::Format_RGB32);  //画布的初始化大小设为400*300，使用32位颜色
    backColor=qRgb(255,255,255);  //画布初始化背景色使用白色
    image.fill(backColor);

    modified=false;
    //modified=true;
    wheelCounter = 1;
    scale=1;
    zoom=1;
    shear=0;
    curShape = Rectanggle;
    setShape(curShape);
       penColor=Qt::red;
       penWidth=1;
       penStyle=Qt::SolidLine;
       isDrawing=false;
       this->setMinimumSize(600,600);
       this->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
       return;
}
void paintWidget::showNewPicture(QModelIndex index)
{
    QString indexString = index.data(Qt::DisplayRole).toString();
    QString slash("\\");
    indexString = workingDictory + slash + indexString;
    bool a = openImage(indexString);
    qDebug(indexString.toAscii().data());
}
//idx.data(Qt::DisplayRole).toString()

bool paintWidget::openImage(QString &fileName)
{
       QImage loadedImage;
       if(!loadedImage.load(fileName))
           return false;

       QSize newSize=loadedImage.size();
       setImageSize(newSize.width(),newSize.height());
       imageSize = newSize;
       image = loadedImage;
       imageAlpha = loadedImage;
       QRegExp reg;
       const QString regStr("\\d+\\.");
       reg.setPattern(regStr);
       reg.indexIn(fileName);
       QString regResult = reg.cap(0);
       qDebug() << regResult;
       regResult = regResult.left(regResult.length() - 1);
       imageNumber = regResult.toInt();
       qDebug() << regResult;
       qDebug("%d",imageNumber);
       modified=false;
       update();
       return true;
}
bool paintWidget::saveImage(const QString &fileName, const char *fileFormat)
{
    QImage visibleImage=image;

       if(visibleImage.save(fileName,fileFormat))  //实现了文件存储
       {
           modified=false;
           return true;
       }
       else
       {
           return false;
       }
}

QSize paintWidget::getImageSize()
{
    return image.size()*scale;
}


void paintWidget::zoomIn()
{
    zoom*= 1.1;
    image = imageAlpha.scaled(imageSize * zoom,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    this->setMinimumSize(image.size());
    qDebug("%d %d",image.size().width(),image.size().height());
    wheelCounter *= 1.1;
    imageAlpha = image;
    update();
}

void paintWidget::zoomOut()
{
    zoom /= 1.1;
    image = imageAlpha.scaled(imageSize * zoom,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    this->setMinimumSize(image.size());
    wheelCounter /= 1.1;
    imageAlpha = image;
    update();
}
void paintWidget::setShape(shapeType shape)
{
   curShape=shape;

}
void paintWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(0,0,image);

}

void paintWidget::mousePressEvent(QMouseEvent *event)
{
    timer.start(300);
    if(event->button()==Qt::LeftButton)  //当鼠标左键按下
       {

           tempPoint1 = lastPoint;
           lastPoint = event->pos();//获得鼠标指针当前坐标作为起始坐标
           isDrawing = true;
       }
}
void paintWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton)  //如果鼠标左键按着的同时移动鼠标
      {
          endPoint=event->pos();  //获得鼠标指针当前坐标作为终止坐标



              isDrawing = false;
              image = imageAlpha;
              paint(image);  //绘制图形
              update();
      }
}
void paintWidget::mouseDoubleClickEvent(QMouseEvent *event)
{

    //fileName = "./result.txt";
    int i,j;
    QString strLine = "";
    QString separator = "\n";
    info.setFile(fileName);
    if(modified == true)
    {
       QString fileName = "./result";
       QFileInfo info("./result");
           QString slash("\\");
           fileName = workingDictory + slash;
           fileName += "ground_truth.txt";

       file.setFileName(fileName);
       fileOut.setFileName(fileName);
       if(!file.exists())
       {
           if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
           {
               QMessageBox::critical(NULL,"提示","创建文件失败");
               return;
           }
           file.close();
       }
       if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
       {
              QMessageBox::critical(NULL,"提示","读取文件失败");
       }
       QTextStream in(&file);
       fileContent = in.readAll();
       file.close();
       fileContentList = fileContent.split("\n");
       if(fileContentList.count() < imageNumber)
       {
           j = imageNumber - fileContentList.count()+2;
           for(i=0;i<j;i++)
               fileContentList.append("\n");
       }
       qDebug() << fileContentList;
       QPoint tempPoint;
       if(tempPoint2.y() - tempPoint1.y() < 0)
       {
           tempPoint.setY(tempPoint1.y());
           tempPoint1.setY(tempPoint2.y());
           tempPoint2.setY(tempPoint.y());
       }
       if(tempPoint2.x() - tempPoint1.x() < 0)
       {
           tempPoint.setX(tempPoint1.x());
           tempPoint1.setX(tempPoint2.x());
           tempPoint2.setX(tempPoint.x());
       }
       strLine = QString::number(tempPoint1.x()/wheelCounter) + " " + QString::number(tempPoint1.y()/wheelCounter) + " " + QString::number((tempPoint2.x() - tempPoint1.x())/wheelCounter) + " " + QString::number((tempPoint2.y() - tempPoint1.y())/wheelCounter);
       fileContentList[imageNumber-1] = strLine;
       fileContent = fileContentList.join(separator);
       if(!fileOut.open(QIODevice::WriteOnly|QIODevice::Text))
       {
           QMessageBox::critical(NULL,"提示","写入文件失败");
           return;
       }
       QTextStream out(&fileOut);
       out << fileContent;
       out.flush();
       fileOut.close();
       penColor = Qt::green;
       paint(image);
       penColor = Qt::red;
       lastPoint = event->pos();
    }
}
void paintWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)  //如果鼠标左键释放
     {
         tempPoint2 = endPoint;
         endPoint = event->pos();//获得鼠标指针当前坐标作为终止坐标
         if(endPoint == lastPoint)
         {
             lastPoint = tempPoint1;
             endPoint = tempPoint2;
         }
         else
         {
         isDrawing=false;
         paint(image);  //绘制图形
         }
     }
}
void paintWidget::wheelEvent(QWheelEvent *event)
{
    if(event->delta() < 0)
    {
        zoomIn();
        qDebug("%lf",scale);
    }
    else
        zoomOut();
}
void paintWidget::setImageSize(int width, int height)
{
    QImage newImage(width,height,QImage::Format_RGB32);
    image=newImage;
    update();
}
void paintWidget::paint(QImage &theImage)
{
    QPainter pp(&theImage);  //在theImage上绘图


       //pp.drawLine(lastPoint,endPoint);  //由起始坐标和终止坐标绘制直线
       //update();  //进行更新界面显示，可引起窗口重绘事件，重绘窗口


   //    QPainter pp(&theImage);  //在zheImage上绘图
       QPen pen=QPen();
       pen.setColor(penColor);
       pen.setStyle(penStyle);
       pen.setWidth(penWidth);
       QBrush brush=QBrush(brushColor);
       pp.setPen(pen);
       QRect rect;

       int x,y,w,h;
       x=lastPoint.x()/scale;
       y=lastPoint.y()/scale;
       w=(endPoint.x()-x)/scale;
       h=(endPoint.y()-y)/scale;

       if(curShape == Rectanggle)
       {
           pp.drawRect(x,y,w,h);

       }

       update();  //进行更新界面显示，可引起窗口重绘事件，重绘窗口
       modified=true;
}
void paintWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_W :
        {
            lastPoint.setY(lastPoint.y() - 1);
            image = imageAlpha;
            paint(image);
            break;
        }
        case Qt::Key_S :
        {
            endPoint.setY(endPoint.y() + 1);
            image = imageAlpha;
            paint(image);
            break;
        }
        case Qt::Key_A :
        {
            lastPoint.setX(lastPoint.x() + 1);
            image = imageAlpha;
            paint(image);
            break;
        }
        case Qt::Key_D :
        {
            endPoint.setX(endPoint.x() - 1);
            image = imageAlpha;
            paint(image);
            break;
        }
        case Qt::Key_Q :
        {
            lastPoint.setY(lastPoint.y() + 1);
            image = imageAlpha;
            paint(image);
            break;
        }
        case Qt::Key_Z :
        {
            lastPoint.setX(lastPoint.x() - 1);
            image = imageAlpha;
            paint(image);
            break;
        }
        case Qt::Key_X :
        {
            endPoint.setY(endPoint.y() - 1);
            image = imageAlpha;
            paint(image);
            break;
        }
        case Qt::Key_C :
        {
            endPoint.setX(endPoint.x() + 1);
            image = imageAlpha;
            paint(image);
            break;
        }
    }
}
void paintWidget::setWorkingDictory(QString &path)
{
    workingDictory = path;
}
void paintWidget::paintKeyEvent(QKeyEvent *event)
{
    keyPressEvent(event);
}
paintWidget::~paintWidget()
{

}
