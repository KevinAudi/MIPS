#include "mipsimage.h"
#include <QDebug>
#include <QApplication>
MipsImage::MipsImage() : QImage()
{
}

MipsImage::MipsImage(const QImage &image) : QImage(image)
{
}


QImage MipsImage::smoothnessGauss(QImage image, MipsWeightMatrix matrix, double modulus)
{
    QImage  gaussedImage;
    if (image.format() == QImage::Format_Indexed8 && image.depth() == 8)
    {
        gaussedImage = gauss8BitImage(image, matrix, modulus);
    }
    else if (image.depth() == 32)
    {
        QImage gaussedRed = gauss8BitImage(singleColorChannel(image, RED), matrix, modulus);
        QImage gaussedGreen = gauss8BitImage(singleColorChannel(image, GREEN), matrix, modulus);
        QImage gaussedBlue = gauss8BitImage(singleColorChannel(image, BLUE), matrix, modulus);
        gaussedImage = mergeColorChannel(gaussedRed, gaussedGreen, gaussedBlue);
    }
    else
    {
        gaussedImage = image;
    }
    return gaussedImage;
}

QImage MipsImage::singleColorChannel(QImage image, ColorChannel channel)
{
    QImage singleChannelImage(image.size(), QImage::Format_Indexed8);
    QVector<QRgb> colors(256);
    for (int i = 0; i < 256; i++)
    {
        colors[i] = qRgb(i, i, i);
    }
    singleChannelImage.setColorTable(colors);
    int w = image.width();
    int h = image.height();
    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            QRgb px = image.pixel(x, y);
#ifdef USE_QT_RGB
            if (channel == MipsImage::RED)
            {
                singleChannelImage.setPixel(x, y, qRed(px));
            }
            else if (channel == MipsImage::GREEN)
            {
                singleChannelImage.setPixel(x, y, qGreen(px));
            }
            else if (channel == MipsImage::BLUE)
            {
                singleChannelImage.setPixel(x, y, qBlue(px));
            }
#else
            singleChannelImage.setPixel(x, y, ((px >> channel) & 0xff));
#endif
        }
    }
    return singleChannelImage;
}

QImage MipsImage::gauss8BitImage(QImage image, MipsWeightMatrix matrix, double modulus)
{
    QImage gaussedImage = image;
    int h = image.height();
    int w = image.width();
    int radius = matrix.getRadius();
    if((image.format()==QImage::Format_Indexed8)&&(image.depth()==8))
    {
        for (int x = radius; x <= w - radius - 1; x++)
        {
            for (int y = radius; y <= h - radius - 1; y++)
            {
                unsigned int px = 0;
                for (int i = -radius; i <= radius; i++)
                {
                    for (int j = -radius; j <= radius; j++)
                    {
                        px += image.pixelIndex(x + i, y + j) * matrix.weightAt(i + radius, j + radius);
                    }
                }
                gaussedImage.setPixel(x, y, px * modulus);
            }
        }
    }
    return gaussedImage;
}

QImage MipsImage::mergeColorChannel(QImage red, QImage green, QImage blue)
{
    QImage mergedImage;
    if (red.size() == green.size() && red.size() == blue.size())
    {
        QSize size = red.size();
        mergedImage = QImage(size, Format_RGB32);
        int w = mergedImage.width();
        int h = mergedImage.height();
        for (int x = 0; x < w; x++)
        {
            for (int y = 0; y < h; y++)
            {
                mergedImage.setPixel(x, y, qRgb(red.pixel(x, y), green.pixel(x, y), blue.pixel(x, y)));
            }
        }
    }
    return mergedImage;
}
