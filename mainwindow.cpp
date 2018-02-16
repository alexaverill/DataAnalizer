#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "data.h"
#include "datapoint.h"
#include "database.h"
#include<QFileDialog>
#include<stack>
#include<QDebug>
#include "localsetting.h"
#include<QSettings>
#include "settings.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //loat in settings.
    QSettings settings("Data", "Data");
    localsettings ls;
    ls.setUserName(settings.value("username").toString());
    ls.setPassword(settings.value("password").toString());
    ls.setDatabaseName(settings.value("databaseName").toString());
    ls.setHostName(settings.value("host").toString());
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
   ui->tempView->addItems(temps);
}
void MainWindow::setupSamplesBox()
{
    Database db;
    QStringList samples = db.returnSamples();
    ui->sampleEntryBox->addItems(samples);
    ui->compoundView->addItems(samples);
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
  ui->fileNameDisp->setText(fileIn);
}

void MainWindow::on_sampleEntryBox_currentTextChanged(const QString &arg1)
{

}

void MainWindow::on_pushButton_2_clicked()
{
    Database d;
    d.setStdDev();
}

void MainWindow::on_ExportCSV_clicked()
{
    this->fileOut = QFileDialog::getSaveFileName(this,tr("Export to CSV"),"",tr("CSV (.csv)"));
    int rxnArea=ui->areaBox->value();
    QString sample= ui->compoundView->currentText();
    int temp =ui->tempView->currentText().toInt();
    Database d;
    //d.generalExport(fileOut);
    d.specificExport(fileOut,sample,rxnArea,temp);
    //check rest of form.
    //then call appropriate export function
}


void MainWindow::on_settings_clicked()
{
    settings set;
    set.exec();
}
