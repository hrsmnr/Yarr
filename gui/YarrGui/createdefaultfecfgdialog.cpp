#include "createdefaultfecfgdialog.h"
#include "ui_createdefaultfecfgdialog.h"

CreateDefaultFECfgDialog::CreateDefaultFECfgDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateDefaultFECfgDialog)
{
    ui->setupUi(this);
}

CreateDefaultFECfgDialog::~CreateDefaultFECfgDialog(){
    delete ui;
}

void CreateDefaultFECfgDialog::on_deFECfgFile_button_clicked(){
    QString qS = QFileDialog::getSaveFileName(this, "FE config filename", "./util/", "FE Config JSON File (*.json)");
    this->ui->deFECfgFile_name->setText(qS);
}

void CreateDefaultFECfgDialog::on_deFECfg_button_clicked(){
    QString filename = this->ui->deFECfgFile_name->text();
    if(filename == ""){
        QMessageBox::warning(this, "ERROR", "Please choose a filename");
        return;
    }
    nlohmann::json j;
    if(this->ui->feTypeCombo->currentText() == "FE-I4B"){
        Fei4 fE(nullptr, 0, 0);
        fE.toFileJson(j);
    }else if(this->ui->feTypeCombo->currentText() == "FE65-P2"){
        Fe65p2 fE(nullptr, 0, 0);
        fE.toFileJson(j);
    }else{
        QMessageBox::warning(this, "ERROR", "Please choose a valid frontend type");
        return;
    }
    QFile oF(filename);
    oF.open(QIODevice::WriteOnly);
    QString qS;
    qS = QString::fromStdString(j.dump(4));
    QTextStream oS(&oF);
    oS << qS;
    oF.close();
    QMessageBox::information(this, "SUCCESS", "Successfully created frontend config file");
    this->close();
}
