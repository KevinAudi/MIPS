#ifndef DISPLAYIMAGEDIALOG_H
#define DISPLAYIMAGEDIALOG_H

#include <QDialog>
#include <QScrollArea>
#include <QLabel>
#include <QHBoxLayout>

class DisplayImageDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DisplayImageDialog(QImage image,QWidget *parent = 0);

public slots:

private:
    QScrollArea *displayScrollArea;
    QLabel *displayLabel;
    QWidget *displayImageWidget;
    QHBoxLayout *hboxLayout;


};

#endif // DISPLAYIMAGEDIALOG_H
