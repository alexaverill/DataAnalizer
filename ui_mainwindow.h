/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpenSettings;
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QComboBox *tempView;
    QLabel *label_6;
    QComboBox *compoundView;
    QLabel *label_10;
    QSpinBox *areaBox;
    QPushButton *ExportCSV;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QComboBox *trialEntryBox;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QComboBox *tempEntryBox;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_3;
    QComboBox *sampleEntryBox;
    QVBoxLayout *verticalLayout;
    QPushButton *selectFile;
    QLineEdit *fileNameDisp;
    QPushButton *processData;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QPushButton *pushButton_2;
    QPushButton *settings;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(831, 538);
        actionOpenSettings = new QAction(MainWindow);
        actionOpenSettings->setObjectName(QStringLiteral("actionOpenSettings"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayoutWidget_2 = new QWidget(centralWidget);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(10, 360, 781, 31));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(horizontalLayoutWidget_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_2->addWidget(label_5);

        tempView = new QComboBox(horizontalLayoutWidget_2);
        tempView->setObjectName(QStringLiteral("tempView"));

        horizontalLayout_2->addWidget(tempView);

        label_6 = new QLabel(horizontalLayoutWidget_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_2->addWidget(label_6);

        compoundView = new QComboBox(horizontalLayoutWidget_2);
        compoundView->setObjectName(QStringLiteral("compoundView"));

        horizontalLayout_2->addWidget(compoundView);

        label_10 = new QLabel(horizontalLayoutWidget_2);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_2->addWidget(label_10);

        areaBox = new QSpinBox(horizontalLayoutWidget_2);
        areaBox->setObjectName(QStringLiteral("areaBox"));
        areaBox->setMinimum(0);
        areaBox->setMaximum(100);
        areaBox->setSingleStep(2);

        horizontalLayout_2->addWidget(areaBox);

        ExportCSV = new QPushButton(horizontalLayoutWidget_2);
        ExportCSV->setObjectName(QStringLiteral("ExportCSV"));

        horizontalLayout_2->addWidget(ExportCSV);

        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 40, 781, 91));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_2->addWidget(label);

        trialEntryBox = new QComboBox(horizontalLayoutWidget);
        trialEntryBox->addItem(QString());
        trialEntryBox->addItem(QString());
        trialEntryBox->addItem(QString());
        trialEntryBox->setObjectName(QStringLiteral("trialEntryBox"));

        verticalLayout_2->addWidget(trialEntryBox);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_3->addWidget(label_2);

        tempEntryBox = new QComboBox(horizontalLayoutWidget);
        tempEntryBox->setObjectName(QStringLiteral("tempEntryBox"));

        verticalLayout_3->addWidget(tempEntryBox);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_4->addWidget(label_3);

        sampleEntryBox = new QComboBox(horizontalLayoutWidget);
        sampleEntryBox->setObjectName(QStringLiteral("sampleEntryBox"));

        verticalLayout_4->addWidget(sampleEntryBox);


        horizontalLayout->addLayout(verticalLayout_4);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        selectFile = new QPushButton(horizontalLayoutWidget);
        selectFile->setObjectName(QStringLiteral("selectFile"));

        verticalLayout->addWidget(selectFile);

        fileNameDisp = new QLineEdit(horizontalLayoutWidget);
        fileNameDisp->setObjectName(QStringLiteral("fileNameDisp"));

        verticalLayout->addWidget(fileNameDisp);


        horizontalLayout->addLayout(verticalLayout);

        processData = new QPushButton(horizontalLayoutWidget);
        processData->setObjectName(QStringLiteral("processData"));

        horizontalLayout->addWidget(processData);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(20, 10, 221, 31));
        QFont font;
        font.setPointSize(16);
        label_7->setFont(font);
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 310, 221, 31));
        label_8->setFont(font);
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(20, 160, 121, 41));
        label_9->setFont(font);
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(20, 210, 211, 23));
        settings = new QPushButton(centralWidget);
        settings->setObjectName(QStringLiteral("settings"));
        settings->setGeometry(QRect(750, 480, 75, 23));
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpenSettings->setText(QApplication::translate("MainWindow", "OpenSettings", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Temperature:", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "Compound", nullptr));
        label_10->setText(QApplication::translate("MainWindow", "Area", nullptr));
        ExportCSV->setText(QApplication::translate("MainWindow", "Export to CSV", nullptr));
        label->setText(QApplication::translate("MainWindow", "Trial", nullptr));
        trialEntryBox->setItemText(0, QApplication::translate("MainWindow", "1", nullptr));
        trialEntryBox->setItemText(1, QApplication::translate("MainWindow", "2", nullptr));
        trialEntryBox->setItemText(2, QApplication::translate("MainWindow", "3", nullptr));

        label_2->setText(QApplication::translate("MainWindow", "Temperature", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Sample", nullptr));
        selectFile->setText(QApplication::translate("MainWindow", "Open File", nullptr));
        processData->setText(QApplication::translate("MainWindow", "Process Data", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "Input Data:", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "Export Data:", nullptr));
        label_9->setText(QApplication::translate("MainWindow", "Calculations", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "Calculate StdDeviation", nullptr));
        settings->setText(QApplication::translate("MainWindow", "Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
