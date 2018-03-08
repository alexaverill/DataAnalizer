#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "datapoint.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString fileIn; //used for input
    QString fileOut; // used to push out data to csv file.
    bool newTrial;
    dataPoint dP;
    void setupTrialDropbox();
    void setupTempDropBox();
    void setupSamplesBox();
private slots:

    void on_trialEntryBox_currentIndexChanged(int index);

    void on_tempEntryBox_currentIndexChanged(int index);

    void on_processData_clicked();

    void on_trialEntryBox_activated(int index);



    void on_selectFile_clicked();

    void on_sampleEntryBox_currentTextChanged(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_ExportCSV_clicked();

    void on_settings_clicked();

    void on_avgBtn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
