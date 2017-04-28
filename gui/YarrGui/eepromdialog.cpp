#include "eepromdialog.h"
#include "ui_eepromdialog.h"

EEPROMDialog::EEPROMDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EEPROMDialog)
    {
        ui->setupUi(this);

        parentCast = dynamic_cast<YarrGui*>(parent);
        if(parentCast == nullptr) {
            std::cerr << "Parent cast failed. Aborting...\n";
            exit(-1);
        }
}

EEPROMDialog::~EEPROMDialog(){
    delete ui;
}

//Read EEPROM, write to editor
void EEPROMDialog::on_buttonReadSBE_clicked(){
    int index = parentCast->getDeviceComboBoxCurrentIndex();
    uint8_t * buffer = new uint8_t[ARRAYLENGTH];
    std::string fName = "util/.tmpRd.sbe";

    parentCast->specVecAt(index)->readEeprom(buffer, ARRAYLENGTH);
    parentCast->specVecAt(index)->createSbeFile(fName, buffer, ARRAYLENGTH);

    ui->SBETextEdit->setText(QString::fromStdString(this->sbeBufToStr(buffer)));

    delete[] buffer;
    return;
}

//Write editor content to EEPROM
void EEPROMDialog::on_buttonWriteSBE_clicked(){
    int index = parentCast->getDeviceComboBoxCurrentIndex();
    uint8_t * buffer = new uint8_t[ARRAYLENGTH];
    std::string pathname = "util/.tmpWr.sbe";
    QFile tmpFile(QString::fromStdString(pathname));
    tmpFile.open(QIODevice::WriteOnly | QIODevice::Text);
    if(!tmpFile.isOpen()){
        std::cerr << "Error creating temporary file '" << pathname << "', aborting... " << std::endl;
        QMessageBox::critical(this, "ERROR",
                              "Error creating temporary file '" + QString::fromStdString(pathname) + "', aborting...");
        return;
    }
    QTextStream tmpFileStream(&tmpFile);
    tmpFileStream << ui->SBETextEdit->toPlainText();
    tmpFile.close();

    parentCast->specVecAt(index)->getSbeFile(pathname, buffer, ARRAYLENGTH);
    parentCast->specVecAt(index)->writeEeprom(buffer, ARRAYLENGTH, 0);

    delete[] buffer;

    QMessageBox::information(this, "Write SBE", "SpecBOARD EEPROM written");

    return;
}

void EEPROMDialog::on_buttonLoadFilename_clicked(){
    QString filename = QFileDialog::getOpenFileName(this,
                                                    "Select EEPROM content file",
                                                    "./",
                                                    "SpecBoard EEPROM content file (*.sbe *.txt *.js *.json);;All (*)");
    ui->sbefile_name->setText(filename);
    return;
}

void EEPROMDialog::on_buttonLoadSBEFile_clicked(){
    uint8_t * p = new uint8_t[ARRAYLENGTH];
    parentCast->specVecAt(parentCast->getDeviceComboBoxCurrentIndex())
              ->getSbeFile(this->ui->sbefile_name->text().toStdString(), p, ARRAYLENGTH);
    this->ui->SBETextEdit->setText(QString::fromStdString(this->sbeBufToStr(p)));

    delete[] p;
    return;
}

void EEPROMDialog::on_buttonSaveFilename_clicked(){
    QString filename = QFileDialog::getSaveFileName(this,
                                                    "Select EEPROM content file",
                                                    "./",
                                                    "SpecBoard EEPROM content file(*.sbe *.txt *.js *.json);;All (*)");
    ui->sbefile_name_3->setText(filename);
    return;
}

void EEPROMDialog::on_buttonSaveSBEFile_clicked(){
    uint8_t * p = new uint8_t[ARRAYLENGTH];
    std::string tmpFName = "util/.tmpSv.sbe";
    std::ofstream oF(tmpFName);
    if(!oF.is_open()){
        std::cerr << "Error creating temporary file '" << tmpFName << "', aborting... " << std::endl;
        QMessageBox::critical(this, "ERROR",
                              "Error creating temporary file '" + QString::fromStdString(tmpFName) + "', aborting...");
        return;
    }
    oF << this->ui->SBETextEdit->toPlainText().toStdString() << std::endl;
    oF.close();

    int index = this->parentCast->getDeviceComboBoxCurrentIndex();
    this->parentCast->specVecAt(index)->getSbeFile(tmpFName, p, ARRAYLENGTH);
    this->parentCast->specVecAt(index)->createSbeFile(this->ui->sbefile_name_3->text().toStdString(), p, ARRAYLENGTH);

    delete[] p;
    return;
}

std::string EEPROMDialog::sbeBufToStr(uint8_t* buffer){
    std::stringstream contentStream;

    contentStream << std::hex;
    contentStream << std::showbase;
    contentStream << std::setw(9) << "addr" << std::setw(5) << "msk" << std::setw(12) << "data" << std::endl;
    //256/6 = 42; 256%6 = 4
    {
        uint16_t a;     //address
        uint8_t  m;     //mask
        uint32_t d;     //data
        for(unsigned int i = 0; i<(ARRAYLENGTH / 6); i++){
            a  = ((buffer[i*6] | (buffer[i*6+1] << 8)) & 0xffc);
            m  = ((buffer[i*6+1] & 0xf0) >> 4);
            d  = (buffer[i*6+2] | (buffer[i*6+3] << 8) | (buffer[i*6+4] << 16) | (buffer[i*6+5] << 24));
            contentStream << std::setw(9) << a << std::setw(5) << (int)m << std::setw(12) << d << std::endl;
        }
    }
    contentStream << std::dec;
    contentStream << std::noshowbase;

    return contentStream.str();
}
