#ifndef MIPSIMAGE_H
#define MIPSIMAGE_H

#include <QImage>
#include <QVector>

class MipsWeightMatrix
{
public:
    MipsWeightMatrix(int radius)
    {
        width = 2 * radius + 1;
        this->weights = QVector<double>(width  * width);
        for (int i = 0; i < width * width; i++)
        {
            weights[i] = 0;
        }
        this->radius = radius;
    }

    double weightAt(int x, int y)
    {
        return weights[x * width + y];
    }

    void setWidgetAt(int x, int y, double value)
    {
        weights[x * width + y] = value;
    }

    int getRadius()
    {
        return radius;
    }

private:
    int radius;
    int width;
    QVector<double> weights;
};

class MipsImage : public QImage
{
public:
    MipsImage();
    MipsImage(const QImage &image);
    QImage smoothnessGauss(QImage image, MipsWeightMatrix matrix, double modulus);
    enum ColorChannel {RED = 16, GREEN = 8, BLUE = 0, ALPHA = 24};
private:
    QImage singleColorChannel(QImage image, ColorChannel channel);
    QImage gauss8BitImage(QImage image, MipsWeightMatrix matrix, double modulus);
    QImage mergeColorChannel(QImage red, QImage green, QImage blue);
};

#endif // MIPSIMAGE_H
