#ifndef IMAGEPREPROCESSING_H
#define IMAGEPREPROCESSING_H

#include <QWidget>
//#include <QImage>

class ImagePreprocessing : public QWidget
{
    Q_OBJECT
public:
    explicit ImagePreprocessing(QWidget *parent = 0);
    QImage image;

public slots:
    void slotsGauss();
};

#endif // IMAGEPREPROCESSING_H
