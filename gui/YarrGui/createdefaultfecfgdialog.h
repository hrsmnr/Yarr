#ifndef CREATEDEFAULTFECFGDIALOG_H
#define CREATEDEFAULTFECFGDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QTextStream>

#include "Fe65p2.h"
#include "Fei4.h"
#include "json.hpp"

namespace Ui {
class CreateDefaultFECfgDialog;
}

class CreateDefaultFECfgDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateDefaultFECfgDialog(QWidget *parent = 0);
    ~CreateDefaultFECfgDialog();

private slots:
    void on_deFECfgFile_button_clicked();
    void on_deFECfg_button_clicked();

private:
    Ui::CreateDefaultFECfgDialog *ui;
};

#endif // CREATEDEFAULTFECFGDIALOG_H
