#ifndef PLOTDIALOG_H
#define PLOTDIALOG_H

#include <fstream>
#include <iostream>

#include <QDialog>
#include <QFileDialog>
#include <QString>

#include "qcustomplot.h"

namespace Ui {
class PlotDialog;
}

class PlotDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlotDialog(QWidget *parent = 0);
    ~PlotDialog();

private slots:
    void on_buttonSavePDF_clicked();

    void on_buttonSaveCSV_clicked();

private:
    Ui::PlotDialog *ui;
};

#endif // PLOTDIALOG_H
