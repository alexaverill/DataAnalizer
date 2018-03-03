/********************************************************************************
** Form generated from reading UI file 'settings.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_settings
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLineEdit *userNameEdit;
    QLabel *label;
    QLineEdit *passwordEdit;
    QLabel *label_2;
    QLineEdit *hostEdit;
    QLabel *label_3;
    QLineEdit *databaseNameEdit;
    QLabel *label_4;

    void setupUi(QDialog *settings)
    {
        if (settings->objectName().isEmpty())
            settings->setObjectName(QStringLiteral("settings"));
        settings->resize(400, 300);
        buttonBox = new QDialogButtonBox(settings);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        formLayoutWidget = new QWidget(settings);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(60, 40, 281, 151));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        userNameEdit = new QLineEdit(formLayoutWidget);
        userNameEdit->setObjectName(QStringLiteral("userNameEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, userNameEdit);

        label = new QLabel(formLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        passwordEdit = new QLineEdit(formLayoutWidget);
        passwordEdit->setObjectName(QStringLiteral("passwordEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, passwordEdit);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        hostEdit = new QLineEdit(formLayoutWidget);
        hostEdit->setObjectName(QStringLiteral("hostEdit"));

        formLayout->setWidget(2, QFormLayout::FieldRole, hostEdit);

        label_3 = new QLabel(formLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        databaseNameEdit = new QLineEdit(formLayoutWidget);
        databaseNameEdit->setObjectName(QStringLiteral("databaseNameEdit"));

        formLayout->setWidget(3, QFormLayout::FieldRole, databaseNameEdit);

        label_4 = new QLabel(formLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);


        retranslateUi(settings);
        QObject::connect(buttonBox, SIGNAL(accepted()), settings, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), settings, SLOT(reject()));

        QMetaObject::connectSlotsByName(settings);
    } // setupUi

    void retranslateUi(QDialog *settings)
    {
        settings->setWindowTitle(QApplication::translate("settings", "Dialog", nullptr));
        label->setText(QApplication::translate("settings", "Username", nullptr));
        label_2->setText(QApplication::translate("settings", "Password", nullptr));
        label_3->setText(QApplication::translate("settings", "Host", nullptr));
        label_4->setText(QApplication::translate("settings", "Database Name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class settings: public Ui_settings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_H
