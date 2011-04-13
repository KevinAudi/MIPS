#include "displayimagedialog.h"

DisplayImageDialog::DisplayImageDialog(QImage image,QWidget *parent) :
        QDialog(parent)
{

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    QWidget *scrollAreaWidgetContents = new QWidget();
    QHBoxLayout *horizontalLayout = new QHBoxLayout(scrollAreaWidgetContents);
    displayLabel = new QLabel(scrollAreaWidgetContents);
    displayLabel->setPixmap(QPixmap::fromImage(image));
    horizontalLayout->addWidget(displayLabel);
    scrollArea->setWidget(scrollAreaWidgetContents);
    hboxLayout = new QHBoxLayout;
    this->setLayout(hboxLayout);
    hboxLayout->addWidget(scrollArea);
}
