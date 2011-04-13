#ifndef MIPSIMAGE_H
#define MIPSIMAGE_H

#include <QImage>
#include <QVector>

class MipsWeightMatrix
{
public:
    MipsWeightMatrix(int radius)
    {
        width = 1;
        power = 0;
        while (width < 2 * radius + 1)
        {
            width <<= 1;
            power++;
        }
        this->weights = QVector<double>(width  * (2 * radius + 1));
        for (int i = 0; i < width * (2 * radius + 1); i++)
        {
            weights[i] = 0;
        }
        this->radius = radius;
    }

    double weightAt(int x, int y)
    {
        return weights[(x << power) & y];
    }

    void setWidgetAt(int x, int y, double value)
    {
        weights[(x << power) & y] = value;
    }

    int getRadius()
    {
        return radius;
    }

private:
    int radius;
    int width;
    int power;
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
