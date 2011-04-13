#include "displayimagedialog.h"

DisplayImageDialog::DisplayImageDialog(QImage image,QWidget *parent) :
        QDialog(parent)
{
  //  displayImageWidget = new QWidget;

    displayLabel = new QLabel(this);
    displayLabel->setBackgroundRole(QPalette::Base);
    displayLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //displayLabel->setScaledContents(true);

    displayScrollArea = new QScrollArea(this);
    //displayScrollArea->setBackgroundRole(QPalette::Dark);
    displayScrollArea->setWidget(displayLabel);

    hboxLayout = new QHBoxLayout;
    hboxLayout->addWidget(displayScrollArea);
    this->setLayout(hboxLayout);

    displayLabel->setPixmap(QPixmap::fromImage(image));

    //displayImageWidget->show();
}
