#include "plotdialog.h"
#include "ui_plotdialog.h"

PlotDialog::PlotDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlotDialog)
{
    ui->setupUi(this);
}

PlotDialog::~PlotDialog()
{
    delete ui;
}

void PlotDialog::on_buttonSavePDF_clicked(){
    QString qS = QFileDialog::getSaveFileName(this,
                                              "Save plot as PDF",
                                              "./",
                                              "Portable Document Format(*.pdf);;All (*)");
    if(qS==""){
        std::cerr << "ERROR! Invalid file name. Aborting... " << std::endl;
        return;
    }
    if(! this->ui->dialogPlot->savePdf(qS))
        std::cerr << "Error saving file. Plot not saved. " << std::endl;
}


void PlotDialog::on_buttonSaveCSV_clicked(){
    QCPColorMap * m = dynamic_cast<QCPColorMap*>(this->ui->dialogPlot->plottable());
    double step1 = (m->data()->keyRange().upper - m->data()->keyRange().lower) / (double)m->data()->keySize();
    double step2 = (m->data()->valueRange().upper - m->data()->valueRange().lower) / (double)m->data()->valueSize();
    double d1 = m->data()->keyRange().lower;
    double d2 = m->data()->valueRange().lower;

    QString qS = QFileDialog::getSaveFileName(this,
                                              "Save plot as CSV",
                                              "./",
                                              "Comma-Separated Values(*.csv *.dat *.txt);;All (*)");

    std::ofstream oF(qS.toStdString());
    for(int i1 = 0; i1<m->data()->keySize(); i1+=1){
        for(int i2 = 0; i2<m->data()->valueSize(); i2+=1){
            oF << d1 << ",\t" << d2 << ",\t" << m->data()->cell(i1, i2) << std::endl;
            d2+=step2;
        }
        d1+=step1;
        d2 = m->data()->valueRange().lower;
    }


//DEBUG
//    for(int i1 = 0; i1<m->data()->keySize(); i1+=1){
//        for(int i2 = 0; i2<m->data()->valueSize(); i2+=1){
//            std::cout << i1 << " (" << d1 << ") " << i2 << " (" << d2 << ") " << m->data()->cell(i1, i2) << std::endl;
//            d2+=step2;
//        }
//        d1+=step1;
//        d2 = m->data()->valueRange().lower;
//    }
}
