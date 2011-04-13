#include "displayimagedialog.h"

DisplayImageDialog::DisplayImageDialog(QImage image,QWidget *parent) :
        QDialog(parent)
{
    displayImageWidget = new QWidget;

    displayLabel = new QLabel;
    displayLabel->setBackgroundRole(QPalette::Base);
    displayLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    displayLabel->setScaledContents(true);

    displayScrollArea = new QScrollArea();
    displayScrollArea->setBackgroundRole(QPalette::Dark);
    displayScrollArea->setWidget(displayLabel);

    hboxLayout = new QHBoxLayout;
    hboxLayout->addWidget(displayScrollArea);
    displayImageWidget->setLayout(hboxLayout);

    displayLabel->setPixmap(QPixmap::fromImage(image));

    displayImageWidget->show();
}
