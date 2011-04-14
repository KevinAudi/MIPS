#include "imagepreprocessing.h"
#include "mipsimage.h"

ImagePreprocessing::ImagePreprocessing(QWidget *parent) :
        QWidget(parent)
{   

}

void ImagePreprocessing::gauss(QImage image)
{
    processedImage = image;
    MipsImage m;
    MipsWeightMatrix matrix(1);
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            int res = i * i + j * j;
            if (res == 0)
            {
                matrix.setWeightAt(i + 1, j + 1, 4);
            }
            else if (res == 1)
            {
                matrix.setWeightAt(i + 1, j + 1, 2);
            }
            else
            {
                matrix.setWeightAt(i + 1, j + 1, 1);
            }
        }
    }
    processedImage = m.smoothnessGauss(image, matrix, 1.0 / 16.0);
    return;
    if((image.format()==QImage::Format_Indexed8)&&(image.depth()==8))
    {
        int h = image.height();
        int w = image.width();

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
            px1 = image.pixelIndex(i,j);
            px2 = image.pixelIndex(i-1,j);
            px3 = image.pixelIndex(i+1,j);
            px4 = image.pixelIndex(i,j-1);
            px5 = image.pixelIndex(i-1,j-1);
            px6 = image.pixelIndex(i+1,j-1);
            px7 = image.pixelIndex(i,j+1);
            px8 = image.pixelIndex(i-1,j+1);
            px9 = image.pixelIndex(i+1,j+1);
            px1 = (1*px5+2*px4+1*px6+2*px2+4*px1+2*px3+1*px8+2*px7+1*px9)/16;
            processedImage.setPixel(i,j,px1);
        }
        processedImage.save("D:\\gauss.bmp");
    }
    else if(image.depth()==32)
    {
        int h = image.height();
        int w = image.width();

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
            px = image.pixel(i,j);
            px1 = qRed(px);
            px = image.pixel(i-1,j);
            px2 = qRed(px);
            px = image.pixel(i+1,j);
            px3 = qRed(px);
            px = image.pixel(i,j-1);
            px4 = qRed(px);
            px = image.pixel(i-1,j-1);
            px5 = qRed(px);
            px = image.pixel(i+1,j-1);
            px6 = qRed(px);
            px = image.pixel(i,j+1);
            px7 = qRed(px);
            px = image.pixel(i-1,j+1);
            px8 = qRed(px);
            px = image.pixel(i+1,j+1);
            px9 = qRed(px);
            red = (1*px5+2*px4+1*px6+2*px2+4*px1+2*px3+1*px8+2*px7+1*px9)/16;
            if(red>255)
                red = 255;
            px = image.pixel(i,j);
            px1 = qGreen(px);
            px = image.pixel(i-1,j);
            px2 = qGreen(px);
            px = image.pixel(i+1,j);
            px3 = qGreen(px);
            px = image.pixel(i,j-1);
            px4 = qGreen(px);
            px = image.pixel(i-1,j-1);
            px5 = qGreen(px);
            px = image.pixel(i+1,j-1);
            px6 = qGreen(px);
            px = image.pixel(i,j+1);
            px7 = qGreen(px);
            px = image.pixel(i-1,j+1);
            px8 = qGreen(px);
            px = image.pixel(i+1,j+1);
            px9 = qGreen(px);
            green = (1*px5+2*px4+1*px6+2*px2+4*px1+2*px3+1*px8+2*px7+1*px9)/16;
            if(green>255)
                green = 255;
            px = image.pixel(i,j);
            px1 = qBlue(px);
            px = image.pixel(i-1,j);
            px2 = qBlue(px);
            px = image.pixel(i+1,j);
            px3 = qBlue(px);
            px = image.pixel(i,j-1);
            px4 = qBlue(px);
            px = image.pixel(i-1,j-1);
            px5 = qBlue(px);
            px = image.pixel(i+1,j-1);
            px6 = qBlue(px);
            px = image.pixel(i,j+1);
            px7 = qBlue(px);
            px = image.pixel(i-1,j+1);
            px8 = qBlue(px);
            px = image.pixel(i+1,j+1);
            px9 = qBlue(px);
            blue = (1*px5+2*px4+1*px6+2*px2+4*px1+2*px3+1*px8+2*px7+1*px9)/16;
            if(blue>255)
                blue = 255;
            processedImage.setPixel(i,j,qRgb(red,green,blue));
        }
        processedImage.save("D:\\123.jpg");
    }
    else
        return ;
}
