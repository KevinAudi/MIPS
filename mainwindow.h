#include <QDirModel>
#include <QTreeWidgetItem>
#include <QLabel>
#include <QScrollArea>
#include <QFileSystemModel>

#include "ui_MainWindow.h"
#include "image_preprocessing.h"

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void on_actionForward_triggered();
    void on_actionBack_triggered();
    void on_actionZoomOut_triggered();
    void on_actionZoomIn_triggered();
    void on_actionActualSize_triggered();
    void on_treeView_clicked(const QModelIndex & index);
    void on_actionAbout_triggered();

private:
    void DisplayImage(const QString &fileName);
    void scaleImage(double factor);
    void UpdateUI();

    QDirModel *dirModel;
    QLabel *imageInfo;
    QDir *dirCurrent;
    QStringList supportFormat;
    QStringList displayFiles;
    QStringList::const_iterator currentFile;
    double scaleFactor;
   // image_preprocessing *ip;
};
