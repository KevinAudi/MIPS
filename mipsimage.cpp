#include "mipsimage.h"

MipsImage::MipsImage() : QImage()
{
}

void MipsImage::gauss()
{
    int h = height();
    int w = width();

    if((format()==QImage::Format_Indexed8)&&(depth()==8))
    {
        for (int row = 1; row <= h - 2; row++)
        {
            for (int col = 1; col <= w - 2; col++)
            {
                unsigned int px = 0;
                for (int i = -1; i <= 1; i++)
                {
                    for (int j = -1; j <= 1; j++)
                    {
                        px += this->pixel(row + i, row + j) * right(i, j);
                    }
                }
                this->setPixel(row, col, px / 16);
            }
        }
    }
    else if(depth()==32)
    {
        for (int row = 1; row <= h - 2; row++)
        {
            for (int col = 1; col <= w - 2; col++)
            {
                unsigned int r = 0, g = 0, b= 0;
                for (int i = -1; i <= 1; i++)
                {
                    for (int j = -1; j <= 1; j++)
                    {
                        r += qRed(this->pixel(row + i, row + j) * right(i, j));
                        g += qGreen(this->pixel(row + i, row + j) * right(i, j));
                        b += qBlue(this->pixel(row + i, row + j) * right(i, j));
                    }
                }
                this->setPixel(row, col, qRgb(r / 16, g / 16, b / 16));
            }
        }
    }
    else
    {
        return ;
    }
}


int MipsImage::right(int i, int j)
{
    int r = i * i + j * j;
    if (r == 0)
    {
        return 4;
    }
    else if (r == 1)
    {
        return 2;
    }
    else if (r == 2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
