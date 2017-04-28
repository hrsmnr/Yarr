#ifndef EEPROMDIALOG_H
#define EEPROMDIALOG_H

#include <iomanip>
#include <iostream>

#include <QDialog>
#include <QFile>
#include <QFileDialog>

#include "yarrgui.h"

class YarrGui;

namespace Ui {
class EEPROMDialog;
}

class EEPROMDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EEPROMDialog(QWidget *parent = 0);
    ~EEPROMDialog();

private slots:
//    void on_wrFromEditButton_clicked();
//    void on_SBEReadButton_clicked();
//    void on_SBEWriteButton_clicked();
//    void on_sbefile_button_2_clicked();
//    void on_sbefile_button_4_clicked();

    void on_buttonReadSBE_clicked();
    void on_buttonWriteSBE_clicked();
    void on_buttonLoadFilename_clicked();
    void on_buttonLoadSBEFile_clicked();
    void on_buttonSaveFilename_clicked();
    void on_buttonSaveSBEFile_clicked();

private:
    Ui::EEPROMDialog *ui;

    YarrGui * parentCast;

    std::string sbeBufToStr(uint8_t*);
};

#endif // EEPROMDIALOG_H
