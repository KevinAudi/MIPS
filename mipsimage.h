#ifndef MIPSIMAGE_H
#define MIPSIMAGE_H

#include <QImage>

class MipsImage : public QImage
{
public:
    MipsImage();
    void gauss();
private:
    int right(int i, int j);
};

#endif // MIPSIMAGE_H
