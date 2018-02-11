#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "data.h"
#include "datapoint.h"
#include "database.h"
#include<QFileDialog>
#include<stack>
#include<QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupTempDropBox();
    setupSamplesBox();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::setupTempDropBox()
{
    Database db;
   QStringList temps = db.returnTemperatures();
   ui->tempEntryBox->addItems(temps);
}
void MainWindow::setupSamplesBox()
{
    Database db;
    QStringList samples = db.returnSamples();
    ui->sampleEntryBox->addItems(samples);
}
void MainWindow::setupTrialDropbox()
{
    Database db;
    std::stack<QString> entries = db.returnTrials();
    //ui->trialEntryBox->addItem();
}
void MainWindow::on_processData_clicked()
{

    dataPoint dP;

    dP.temperature = ui->tempEntryBox->currentText().toInt();
    dP.trial = ui->trialEntryBox->currentText().toInt();
    dP.compound = ui->sampleEntryBox->currentText();
    if(dP.trial <=0 || dP.compound <=0 || dP.temperature <=0)
    {
        return; //Not all are filled in.
    }
    Data d(this->fileIn);
    d.processFile(&dP);
}

void MainWindow::on_trialEntryBox_currentIndexChanged(int index)
{
    this->dP.trial = index;
}

void MainWindow::on_tempEntryBox_currentIndexChanged(int index)
{
    this->dP.temperature = index;
}

void MainWindow::on_trialEntryBox_activated(int index)
{

}


void MainWindow::on_selectFile_clicked()
{
  this->fileIn = QFileDialog::getOpenFileName(this,tr("Open File"),"");
}

void MainWindow::on_sampleEntryBox_currentTextChanged(const QString &arg1)
{

}
