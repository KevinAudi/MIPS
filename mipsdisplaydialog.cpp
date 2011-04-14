#include "mipsdisplaydialog.h"
#include <QHBoxLayout>
#include <QLabel>
MipsDisplayDialog::MipsDisplayDialog(QImage image, QWidget *parent) :
    QDialog(parent)
{
    QHBoxLayout *layout = new QHBoxLayout;
    QLabel *label = new QLabel(this);
    layout->addWidget(label);
    label->setPixmap(QPixmap::fromImage(image));
}
