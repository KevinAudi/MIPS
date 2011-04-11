#include <QMessageBox>
#include <QHeaderView>
#include <QScrollBar>
#include <QImageReader>


#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), scaleFactor(1)
{
    setupUi(this);

    image_preprocessing *ip = new image_preprocessing;

    QObject::connect(actionGauss,SIGNAL(triggered()),ip,SLOT(Gauss()));


    dirModel = new QDirModel(this);
    dirModel->setFilter(QDir::Dirs | QDir::Drives| QDir::NoDotAndDotDot);

    dirCurrent = new QDir();

    imageInfo = new QLabel(this);
    imageInfo->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    imageInfo->setAlignment(Qt::AlignCenter);
    imageInfo->setStatusTip(tr("Display image infomation in the selected folder"));

    mainToolBar->addWidget(imageInfo);

    treeView->setModel(dirModel);
    treeView->header()->setVisible(false);
    treeView->setColumnHidden(1,true);	// Size
    treeView->setColumnHidden(2,true);  // Type
    treeView->setColumnHidden(3,true);  // Modified Date

    foreach (QByteArray ba, QImageReader::supportedImageFormats())
    {
        QString ext = QString("*.")+QString(ba);
        supportFormat<<ext;
    }
    resize(780,580);
    currentFile = displayFiles.constBegin();
    UpdateUI();
}

MainWindow::~MainWindow()
{
    delete dirCurrent;
}

void adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
     }

void MainWindow::scaleImage(double factor)
{
    Q_ASSERT(label->pixmap());
    scaleFactor *= factor;
    label->resize(scaleFactor * label->pixmap()->size());

     adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
     adjustScrollBar(scrollArea->verticalScrollBar(), factor);
}

void MainWindow::DisplayImage(const QString &fileName)
{
    QImage image(fileName);
    if (image.isNull()) {
        QMessageBox::information(this, tr("Image Viewer"),
                                 tr("Cannot load %1.").arg(fileName));
        return;
    }
    label->setPixmap(QPixmap::fromImage(image));
    scaleImage(1.0);
}

void MainWindow::UpdateUI()
{
    if(currentFile == displayFiles.constEnd())
    {
        imageInfo->setText(tr("No Images, Click TreeView to select pic folder"));
        actionForward->setEnabled(false);
        actionBack->setEnabled(false);
        actionZoomIn->setEnabled(false);
        actionZoomOut->setEnabled(false);
        actionActualSize->setEnabled(false);
    }
    else
    {
        int i = displayFiles.indexOf(*currentFile, 0) + 1;	// non-Programmer count from 1 instead 0
        imageInfo->setText(QString(tr("%1/%2 %3 %4%")).arg(i).arg(displayFiles.size()).arg(*currentFile).arg(scaleFactor*100, 3));
        actionForward->setEnabled(true);
        actionBack->setEnabled(true);
        actionZoomIn->setEnabled(true);
        actionZoomOut->setEnabled(true);
        actionActualSize->setEnabled(true);
    }
    actionZoomIn->setEnabled(scaleFactor < 3.0);
    actionZoomOut->setEnabled(scaleFactor > 0.333);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QRect childRect=scrollArea->childrenRect();
    label->resize(childRect.size());
}

void MainWindow::on_actionForward_triggered()
{
    currentFile++;
    if(currentFile == displayFiles.constEnd())
        currentFile = displayFiles.constBegin();
    DisplayImage(dirCurrent->absoluteFilePath(*currentFile));
    UpdateUI();
}

void MainWindow::on_actionBack_triggered()
{
    if(currentFile == displayFiles.constBegin())
        currentFile = displayFiles.constEnd();
    currentFile--;
    DisplayImage(dirCurrent->absoluteFilePath(*currentFile));
    UpdateUI();
}

void MainWindow::on_actionZoomOut_triggered()
{
    scaleImage(0.8);
    UpdateUI();
}

void MainWindow::on_actionZoomIn_triggered()
{
    scaleImage(1.25);
    UpdateUI();
}

void MainWindow::on_actionActualSize_triggered()
{
    scaleFactor = 1.0;
    scaleImage(1.0);
    UpdateUI();
}

void MainWindow::on_treeView_clicked ( const QModelIndex &index )
{
    const QString path = dirModel->data(index, QDirModel::FilePathRole).toString();
    dirCurrent->setPath(path);
    displayFiles = dirCurrent->entryList(supportFormat, QDir::Files);
    currentFile = displayFiles.constBegin();
    if(currentFile != displayFiles.constEnd())
        DisplayImage(dirCurrent->absoluteFilePath(*currentFile));
    UpdateUI();
}

const char *htmlAboutText =
        "<HTML>"
        "<p>The MIPS (Medical Image Preprocessing System) is mainly designed to enhance the medical images.</p>"
        "<p>This program is subject to the GPL license.</p>"
        "<p>Written by Kevin Chow.</p>"
        "<p>Current Version 0.9.1"
        "</HTML>";

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About The MIPS"), htmlAboutText);
}

