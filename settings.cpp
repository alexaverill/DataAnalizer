#include "settings.h"
#include "ui_settings.h"
#include<QSettings>
#include "localsetting.h"
settings::settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);
    localsettings ls;
    ui->databaseNameEdit->setText(ls.returnDatabaseName());
    ui->hostEdit->setText(ls.returnHost());
    ui->userNameEdit->setText(ls.returnUserName());
    ui->passwordEdit->setText(ls.returnPassword());
}

settings::~settings()
{
    delete ui;
}

void settings::on_buttonBox_accepted()
{
    localsettings ls;
    ls.setDatabaseName(ui->databaseNameEdit->text());
    ls.setHostName(ui->hostEdit->text());
    ls.setPassword(ui->passwordEdit->text());
    ls.setUserName(ui->userNameEdit->text());
    QSettings settings("Data", "Data");
    settings.setValue("username",ls.returnUserName());
    settings.setValue("password",ls.returnPassword());
    settings.setValue("databaseName",ls.returnDatabaseName());
    settings.setValue("host",ls.returnHost());
}
