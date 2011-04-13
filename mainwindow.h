#include <QDirModel>
#include <QTreeWidgetItem>
#include <QLabel>
#include <QScrollArea>

#include "ui_MainWindow.h"
#include "imagepreprocessing.h"

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionForward_triggered();
    void on_actionBack_triggered();
    void on_actionZoomOut_triggered();
    void on_actionZoomIn_triggered();
    void on_actionActualSize_triggered();
    void on_actionAbout_triggered();
    void hxImage();

    void on_treeView_clicked(const QModelIndex & index);    

private:
    void displayImage(const QString &fileName);
    void scaleImage(double factor);
    void updateUi();


    QDirModel *dirModel;
    QLabel *imageInfo;
    QDir *currentDirectory;
    QStringList supportedFormat;
    QStringList displayFiles;
    QStringList::const_iterator currentFile;
   // QString currentFile;
    double scaleFactor;
    ImagePreprocessing *ip;
};
