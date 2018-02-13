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
int Database::getTempID(int temp){
    //connect();
    QSqlQuery query;
    query.prepare("SELECT idTemperatures from Temperatures where temperature=?");
    query.addBindValue(temp);
    query.exec();
    while(query.next()){
        int id = query.value(0).toInt();
        query.finish();
     //   close();
        return id;
    }
    query.finish();
   // close();
    return -1;
}
int Database::getSampleID(QString compoundName)
{
    //connect();
    QSqlQuery query;
    query.prepare("SELECT idSamples from Samples where SampleName=?");
    query.addBindValue(compoundName);
    query.exec();
    while(query.next()){
        int id = query.value(0).toInt();
        query.finish();
        return id;
    }
    query.finish();
    return -1;
}
bool Database::insertData(dataPoint *dP)
{
    connect();
    //start by checking to see if trial exists
    // trial has trial ID, Trial TEMP and sample
    //if it exists use the ID to map the raw data to trial.
    //if it doesn't create new trial and use that ID.
    int sampleID = getSampleID(dP->compound);
    int tempID = getTempID(dP->temperature);
    int trialID = 0;
    QSqlQuery checkTrial(db);
    checkTrial.prepare("SELECT idtrial from trial where replicantID=? AND sampleID=? and temperatureID=?");
    checkTrial.addBindValue(dP->trial);
    checkTrial.addBindValue(sampleID);
    checkTrial.addBindValue(tempID);
    checkTrial.exec();
    if(!checkTrial.first()){
        //insert trial and return id.
        QSqlQuery insertTrial(db);
        insertTrial.prepare("INSERT INTO trial(replicantID,sampleID,temperatureID)values(?,?,?);");
        insertTrial.addBindValue(dP->trial);
        insertTrial.addBindValue(sampleID);
        insertTrial.addBindValue(tempID);
        insertTrial.exec();
        trialID = insertTrial.lastInsertId().toInt();
        insertTrial.finish();
    }else{
        trialID = checkTrial.value(0).toInt();
        checkTrial.finish();
    }
    checkTrial.finish();
    //qDebug()<<checkTrial.first();
    if(trialID <=0 ){
        return false;
    }
    QSqlQuery query(db);

    //insert raw data
    query.prepare("INSERT INTO `mydb`.`data` (`trialID`, `rxntemp`, `rxnTime`, `rxnheatFlow`, `rxnrevCP`, `rxnarea`) VALUES (?, ?, ?, ?, ?, ?);");
    query.addBindValue(trialID);
    query.addBindValue(dP->rxnTemp);
    query.addBindValue(dP->rxnTime);
    query.addBindValue(dP->rxnHeat);
    query.addBindValue(dP->rxnRevCP);
    query.addBindValue(dP->rxnArea);
    query.exec();
    //qDebug()<< query.lastError();
    query.finish();
    close();
}

float Database::calculateAvg(int sampleID,int temp,int areaVal)
{
    /*SQL query to get average when given a sample, a temperature and then loop through to get values at each step.
     *
     * select AVG(rxnTime) from mydb.data where trialID in
     *  (select idTrial from mydb.trial where sampleID=1 and temperatureID=1) and rxnArea=4;
     * */
}
