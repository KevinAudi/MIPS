#ifndef IMAGEPREPROCESSING_H
#define IMAGEPREPROCESSING_H

#include <QWidget>
#include <QImage>

class ImagePreprocessing : public QWidget
{
    Q_OBJECT
public:
    explicit ImagePreprocessing(QWidget *parent = 0);

public slots:
    void slotsGauss();

private:
    QImage image;

};

#endif // IMAGEPREPROCESSING_H
