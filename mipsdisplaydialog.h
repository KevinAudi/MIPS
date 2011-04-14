#ifndef MIPSDISPLAYDIALOG_H
#define MIPSDISPLAYDIALOG_H

#include <QDialog>

class MipsDisplayDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MipsDisplayDialog(QImage image, QWidget *parent = 0);

signals:

public slots:

};

#endif // MIPSDISPLAYDIALOG_H
