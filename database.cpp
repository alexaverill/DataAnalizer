#include "database.h"
#include "datapoint.h"
#include<QDebug>
#include <QSqlQuery>
#include<QVariant>
#include <QSqlError>

Database::Database()
{
    //eventually load from config file.

}
bool Database::connect()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(host);
    db.setDatabaseName(databaseName);
    db.setUserName(username);
    db.setPassword(password);
    return db.open();
}
void Database::close()
{
    QString connection;
    connection = db.connectionName();
    db.close();
    db = QSqlDatabase();
    db.removeDatabase(connection);
}

std::stack<QString> Database::returnTrials()
{
    connect();
    //QSqlQuery query("Select ";
    close();
}
QStringList Database::returnTemperatures()
{
    QStringList output;
    connect();
    QSqlQuery query("Select * from mydb.Temperatures;");
    while(query.next()){
        output.append(query.value(1).toString());
    }
    close();
    return output;
}
QStringList Database::returnSamples()
{
    QStringList output;
    connect();
    QSqlQuery query("Select * from mydb.Samples;");
    while(query.next()){
        output.append(query.value(1).toString());
    }
    close();
    return output;
}
int Database::getSampleID(QString compoundName)
{
    connect();
    QSqlQuery query;
    query.prepare("SELECT idSamples from Samples where SampleName=?");
    query.bindValue(compoundName);
    query.exec();
    return query.value(0).toInt();
}
bool Database::insertData(dataPoint *dP)
{
    connect();
    //start by checking to see if trial exists
    // trial has trial ID, Trial TEMP and sample
    //if it exists use the ID to map the raw data to trial.
    //if it doesn't create new trial and use that ID.
    int sampleID = getSampleID(dP->compound);
    QSqlQuery checkTrial(db);
    checkTrial.prepare("SELECT idtrial from trial where replicantID=? AND sampleID=? and temperatureID=?");
    checkTrial.bindValue(dP->trial);
    checkTrial.bindValue(sampleID);
    checkTrial.bindValue(dP->temperature);
    checkTrial.exec();
    if(checkTrial.value(0)>0){

    }

    QSqlQuery query(db);

    //insert raw data
    query.prepare("INSERT INTO `mydb`.`data` (`trialID`, `rxntemp`, `rxnTime`, `rxnheatFlow`, `rxnrevCP`, `rxnarea`) VALUES (?, ?, ?, ?, ?, ?);");
    query.addBindValue(dP->trial);
    query.addBindValue(dP->rxnTemp);
    query.addBindValue(dP->rxnTime);
    query.addBindValue(dP->rxnHeat);
    query.addBindValue(dP->rxnRevCP);
    query.addBindValue(dP->rxnArea);
    query.exec();
    qDebug()<< query.lastError();
    query.finish();
    close();
}

