#ifndef IMAGE_PREPROCESSING_H
#define IMAGE_PREPROCESSING_H

#include <QWidget>
#include <QDesktopWidget>
#include <QPainter>

#include "ui_mainwindow.h"

class image_preprocessing : public QWidget,private Ui::MainWindow
{
    Q_OBJECT

public:
    image_preprocessing(QWidget* parent=0);

    void setPixmap(QString fileName);
    QImage getPixmap();
    void setAngle(qreal rotateAngle);

    bool bFit;
    qreal scale;

protected:
    void paintEvent(QPaintEvent *event);

public slots:
   // void on_actionGauss_triggered();//¸ßË¹Æ½»¬
    void Gauss();
  //  void edgeDetecting();  //±ßÔµ¼ì²â

private:
    QImage pixmap;
    qreal angle;
    int biasx;
    int biasy;
};

#endif // IMAGE_PREPROCESSING_H
