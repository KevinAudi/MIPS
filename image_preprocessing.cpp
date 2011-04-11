#include "image_preprocessing.h"
#include <QtCore>

image_preprocessing::image_preprocessing(QWidget* parent):QWidget(parent)
{
    QDesktopWidget desktop;
    pixmap = QImage(desktop.width(),desktop.height(),QImage::Format_Indexed8);
    scale = 1;
    angle = 0;
    bFit = true;
    biasx = 0;
    biasy = 0;
}

void image_preprocessing::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(angle)
    {
        QPointF center(this->width()/2.0,this->height()/2.0);
        painter.translate(center);
        painter.rotate(angle);
        painter.translate(-center);
    }
    if(bFit)
    {
        QImage fitmap=pixmap.scaled(width(),height(),Qt::KeepAspectRatio);
        painter.drawImage(biasx,biasy,fitmap);
    }
    else
    {
        painter.drawImage(biasx,biasy,pixmap);
    }
}

void image_preprocessing::setPixmap(QString fileName)
{
    pixmap.load(fileName);
    update();
}

QImage image_preprocessing::getPixmap()
{
    return pixmap;
}

void image_preprocessing::setAngle(qreal rotateAngle)
{
    angle +=rotateAngle;
    update();
}

void image_preprocessing::Gauss()
//void image_preprocessing::on_actionGauss_triggered()
{
    qDebug("ABC");
    if((pixmap.format()==QImage::Format_Indexed8)&&(pixmap.depth()==8))
    {
        int h = pixmap.height();
        int w = pixmap.width();

        unsigned int px1;
        unsigned int px2;
        unsigned int px3;
        unsigned int px4;
        unsigned int px5;
        unsigned int px6;
        unsigned int px7;
        unsigned int px8;
        unsigned int px9;

        for(int i = 0; i < w; i++)
            for(int j = 0;j < h; j++)
            {
                if((i < 1)||(j < 1)||(i > w-2)||(j > h-2))
                    continue;
                px1 = pixmap.pixelIndex(i,j);
                px2 = pixmap.pixelIndex(i-1,j);
                px3 = pixmap.pixelIndex(i+1,j);
                px4 = pixmap.pixelIndex(i,j-1);
                px5 = pixmap.pixelIndex(i-1,j-1);
                px6 = pixmap.pixelIndex(i+1,j-1);
                px7 = pixmap.pixelIndex(i,j+1);
                px8 = pixmap.pixelIndex(i-1,j+1);
                px9 = pixmap.pixelIndex(i+1,j+1);
                px1 = (1*px5+2*px4+1*px6+2*px2+4*px1+2*px3+1*px8+2*px7+1*px9)/16;
                pixmap.setPixel(i,j,px1);
            }
        this->update();
    }
    else if(pixmap.depth()==32)
    {
        int h = pixmap.height();
        int w = pixmap.width();
        unsigned int px1;
        unsigned int px2;
        unsigned int px3;
        unsigned int px4;
        unsigned int px5;
        unsigned int px6;
        unsigned int px7;
        unsigned int px8;
        unsigned int px9;
        unsigned int red;
        unsigned int green;
        unsigned int blue;
        QRgb px;
        for(int i = 0;i<w;i++)
            for(int j = 0;j<h;j++)
            {
                if((i<1)||(j<1)||(i>w-2)||(j>h-2))
                    continue;
                px = pixmap.pixel(i,j);
                px1 = qRed(px);
                px = pixmap.pixel(i-1,j);
                px2 = qRed(px);
                px = pixmap.pixel(i+1,j);
                px3 = qRed(px);
                px = pixmap.pixel(i,j-1);
                px4 = qRed(px);
                px = pixmap.pixel(i-1,j-1);
                px5 = qRed(px);
                px = pixmap.pixel(i+1,j-1);
                px6 = qRed(px);
                px = pixmap.pixel(i,j+1);
                px7 = qRed(px);
                px = pixmap.pixel(i-1,j+1);
                px8 = qRed(px);
                px = pixmap.pixel(i+1,j+1);
                px9 = qRed(px);
                red = (1*px5+2*px4+1*px6+2*px2+4*px1+2*px3+1*px8+2*px7+1*px9)/16;
                if(red>255)
                    red = 255;
                px = pixmap.pixel(i,j);
                px1 = qGreen(px);
                px = pixmap.pixel(i-1,j);
                px2 = qGreen(px);
                px = pixmap.pixel(i+1,j);
                px3 = qGreen(px);
                px = pixmap.pixel(i,j-1);
                px4 = qGreen(px);
                px = pixmap.pixel(i-1,j-1);
                px5 = qGreen(px);
                px = pixmap.pixel(i+1,j-1);
                px6 = qGreen(px);
                px = pixmap.pixel(i,j+1);
                px7 = qGreen(px);
                px = pixmap.pixel(i-1,j+1);
                px8 = qGreen(px);
                px = pixmap.pixel(i+1,j+1);
                px9 = qGreen(px);
                green = (1*px5+2*px4+1*px6+2*px2+4*px1+2*px3+1*px8+2*px7+1*px9)/16;
                if(green>255)
                    green = 255;
                px = pixmap.pixel(i,j);
                px1 = qBlue(px);
                px = pixmap.pixel(i-1,j);
                px2 = qBlue(px);
                px = pixmap.pixel(i+1,j);
                px3 = qBlue(px);
                px = pixmap.pixel(i,j-1);
                px4 = qBlue(px);
                px = pixmap.pixel(i-1,j-1);
                px5 = qBlue(px);
                px = pixmap.pixel(i+1,j-1);
                px6 = qBlue(px);
                px = pixmap.pixel(i,j+1);
                px7 = qBlue(px);
                px = pixmap.pixel(i-1,j+1);
                px8 = qBlue(px);
                px = pixmap.pixel(i+1,j+1);
                px9 = qBlue(px);
                blue = (1*px5+2*px4+1*px6+2*px2+4*px1+2*px3+1*px8+2*px7+1*px9)/16;
                if(blue>255)
                    blue = 255;
                pixmap.setPixel(i,j,qRgb(red,green,blue));
            }
        this->update();
    }
    else
        return ;
}
