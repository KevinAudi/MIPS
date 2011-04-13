#ifndef IMAGEPREPROCESSING_H
#define IMAGEPREPROCESSING_H

#include <QWidget>

class ImagePreprocessing : public QWidget
{
    Q_OBJECT
public:
    explicit ImagePreprocessing(QWidget *parent = 0);
    QImage processingImage;
    QImage processedImage;
    void gauss(QImage image);


};

#endif // IMAGEPREPROCESSING_H
