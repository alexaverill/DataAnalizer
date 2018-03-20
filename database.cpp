#include "database.h"
#include "datapoint.h"
#include<QDebug>
#include <QSqlQuery>
#include<QVariant>
#include <QSqlError>
#include<QFile>
#include<QtMath>
#include "localsetting.h"
Database::Database()
{
    //eventually load from config file.
   connect();
}
/*Database::~Database()
{
    this->close();
}*/
bool Database::connect()
{
    localsettings ls;
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(ls.returnHost());
    db.setDatabaseName(ls.returnDatabaseName());
    db.setUserName(ls.returnUserName());
    db.setPassword(ls.returnPassword());
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
    //connect();
    //QSqlQuery query("Select ";
    close();
    std::stack<QString> rtn;
    return rtn;
}
QStringList Database::returnTemperatures()
{
    QStringList output;
    //connect();
    QSqlQuery query("Select * from mydb.Temperatures;");
    while(query.next()){
        output.append(query.value(1).toString());
    }
    //close();
    return output;
}
QStringList Database::returnSamples()
{
    QStringList output;
    //connect();
    QSqlQuery query("Select * from mydb.Samples;");
    while(query.next()){
        output.append(query.value(1).toString());
    }
    //close();
    return output;
}
QList<int> Database::returnSampleID()
{
    QList<int> output;
    QSqlQuery query("Select idSamples from mydb.samples;");
    while(query.next()){
        output.append(query.value(0).toInt());
    }
    //close();
    return output;
}
QList<int> Database::returnTempID()
{
    QList<int> output;
    QSqlQuery query("Select idTemperatures from mydb.Temperatures;");
    while(query.next()){
        output.append(query.value(0).toInt());
    }
    //close();
    return output;
}
int Database::getTempID(int temp){
    //connect();
    QSqlQuery tempq;
   tempq.prepare("SELECT idTemperatures from Temperatures where temperature=?");
    tempq.addBindValue(temp);
    tempq.exec();
    while(tempq.next()){
        int id = tempq.value(0).toInt();
        tempq.finish();
     //   close();
        return id;
    }
    tempq.finish();
   // close();
    return -1;
}
int Database::getSampleID(QString compoundName)
{
    //connect();
    QSqlQuery sample;
    sample.prepare("SELECT idSamples from Samples where SampleName=?");
    sample.addBindValue(compoundName);
    sample.exec();
    while(sample.next()){
        int id = sample.value(0).toInt();
        sample.finish();
        return id;
    }
    sample.finish();
    return -1;
}
bool Database::insertData(dataPoint *dP)
{
    //connect();
    //start by checking to see if trial exists
    // trial has trial ID, Trial TEMP and sample
    //if it exists use the ID to map the raw data to trial.
    //if it doesn't create new trial and use that ID.
    int sampleID = getSampleID(dP->compound);
    int tempID = getTempID(dP->temperature);
    int trialID = 0;
    QSqlQuery checkTrial(db);
    checkTrial.prepare("SELECT idtrial from trial where replicantID=? AND sampleID=? and temperatureID=?");
    //qDebug() << dP->trial << sampleID << tempID;
    checkTrial.addBindValue(dP->trial);
    checkTrial.addBindValue(sampleID);
    checkTrial.addBindValue(tempID);
    checkTrial.exec();
    if(!checkTrial.first()){
        //insert trial and return id.
        QSqlQuery insertTrial(db);
        insertTrial.prepare("INSERT INTO trial(replicantID,sampleID,temperatureID)values(?,?,?);");
        //qDebug() << dP->trial << sampleID << tempID;
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

    if(trialID <=0 ){
        return false;
    }
    QSqlQuery query(db);

    //insert raw data
    query.prepare("INSERT INTO `mydb`.`data` (`trialID`, `rxntemp`, `rxnTime`, `rxnheatFlow`, `rxnrevCP`, `rxnarea`,ln,T) VALUES (?, ?, ?, ?, ?, ?,?,?);");
    query.addBindValue(trialID);
    query.addBindValue(dP->rxnTemp);
    query.addBindValue(dP->rxnTime);
    query.addBindValue(dP->rxnHeat);
    query.addBindValue(dP->rxnRevCP);
    query.addBindValue(dP->rxnArea);
    query.addBindValue(dP->ln);
    query.addBindValue(dP->T);
    query.exec();
    /*if(query.lastError()){
        qDebug()<< query.lastError();
    }*/
    query.finish();
    //close();
}
float Database::returnAvg(QString SampleName, int temp, int rxnArea)
{
    /*select avg(rxnTime) from mydb.trial left join(mydb.data)
    ON (trial.idtrial = data.trialID) where sampleID=1 AND temperatureID=1 and rxnArea=2;
    */
    int SampleID = getSampleID(SampleName);
    QSqlQuery av(db);
    av.prepare("select avg(rxnTime) from mydb.trial left join(mydb.data)ON (trial.idtrial = data.trialID) where sampleID=? AND temperatureID=? and rxnArea=?;");
    av.addBindValue(SampleID);
    av.addBindValue(temp);
    av.addBindValue(rxnArea);
    av.exec();
    while(av.next()){
        qDebug() << av.value(0).toFloat();
    }
    return 1;
}
void Database::setStdDev()
{
    /*
     * 
     * update mydb.data set stdDev=(select * from(SELECT (sqrt(1/3)*pow(rxnTime-(select avg(rxnTime) as dev from mydb.trial left join(mydb.data)
ON (trial.idtrial = data.trialID) where sampleID=1 AND temperatureID=1 and rxnArea=4),2)) from mydb.data where trialID=4 and rxnArea=4) as x) where trialID=1 and rxnArea=4;
*/
    // this function will loop through the trials and then calculate the standard deviation for each percentage. 
    //select each id
    //get sampleID
    QList<int> sampleID = returnSampleID();
    QList<int> tempID = returnTempID();
    for(auto x: sampleID)
    {
        //qDebug()<<x;
        for(auto t: tempID)
        {
            qDebug()<< x << t;
            // get a QList of idTrials from the trials table and then iterate through that to update StdDeviation
            QSqlQuery trials(db);
            trials.prepare("SELECT idTrial from trial where sampleID=? and temperatureID=?");
            trials.addBindValue(x);
            trials.addBindValue(t);
            trials.exec();
            while(trials.next())
            {
                int trialID = trials.value(0).toInt();
                for(int z=2;z<=100;z+=2)
                {
                    //loop through and calculate standard deviation of each item.
                    //There really should be a better way to do this. I know that it has to exist.
                    QSqlQuery update(db);
                    update.prepare("update data set stdDev=(select * from(SELECT (sqrt(1/3)*pow(rxnTime-(select avg(rxnTime) "
                                   "as dev from trial left join(data) ON (trial.idtrial = data.trialID) where sampleID=? "
                                   "AND temperatureID=? and rxnArea=?),2)) "
                                   "from mydb.data where trialID=? and rxnArea=?) as x) where trialID=? and rxnArea=?");
                    update.addBindValue(x);
                    update.addBindValue(t);
                    update.addBindValue(z);
                    update.addBindValue(trialID);
                    update.addBindValue(z);
                    update.addBindValue(trialID);
                    update.addBindValue(z);
                    //now pray.
                    update.exec();
                }
            }



        }
    }
    //get TemperatureID
}
float Database::calculateAvg()
{
    /*SQL query to get average when given a sample, a temperature and then loop through to get values at each step.
     *
     * select AVG(rxnTime) from mydb.data where trialID in
     *  (select idTrial from mydb.trial where sampleID=1 and temperatureID=1) and rxnArea=4;
     * */
    //calculate entire average for all samples, temperatures and areas;
    QList<int> sampleID = returnSampleID();
    QList<int> tempID = returnTempID();
    for(auto x: sampleID)
    {

        for(auto t: tempID)
        {
            qDebug()<< x << t;
            // get a QList of idTrials from the trials table and then iterate through that to update StdDeviation
            QSqlQuery trials(db);
            trials.prepare("SELECT idTrial from trial where sampleID=? and temperatureID=?");
            trials.addBindValue(x);
            trials.addBindValue(t);
            trials.exec();
            while(trials.next())
            {
                int trialID = trials.value(0).toInt();
                for(int z=2;z<=100;z+=2)
                {
                    //loop through and calculate standard deviation of each item.
                    //There really should be a better way to do this. I know that it has to exist.
                    QSqlQuery update(db);
                    update.prepare("update data set average=(select avg(rxnTime)"
                                   "as dev  from trial join(SELECT * FROM data)as data ON (trial.idtrial = data.trialID) where sampleID=? "
                                   "AND temperatureID=? and rxnArea=?) where trialID=? and rxnArea=?");
                    update.addBindValue(x);
                    update.addBindValue(t);
                    update.addBindValue(z);
                    update.addBindValue(trialID);
                    update.addBindValue(z);
                    //now pray.
                    update.exec();
                }
            }



        }
    }
    return 0;
}
void Database::generalExport(QString fileName)
{
    //query to export all data;
    //select SampleName,temperature,replicantID,rxnTime,rxnArea,ln,T,stdDev from mydb.data join (mydb.trial, mydb.samples,mydb.temperatures) on (data.trialID=trial.idTrial and samples.idSamples = trial.sampleID and temperatures.idTemperatures= trial.temperatureid);
    QSqlQuery getData(db);
    getData.prepare("select SampleName,replicantID,temperature,rxnTime,rxnArea,ln,T,average,stdDev from mydb.data join (mydb.trial, mydb.samples,mydb.temperatures) on (data.trialID=trial.idTrial and samples.idSamples = trial.sampleID and temperatures.idTemperatures= trial.temperatureid);");
    getData.exec();
    while(getData.next())
    {
        qDebug() << getData.value(0).toString()<<","<< getData.value(1).toInt()<<","<< getData.value(2).toInt()<< ","<<getData.value(3).toFloat()<<","<< getData.value(4).toInt()<<","<< getData.value(5).toFloat()<<","<< getData.value(6).toFloat()<<","<< getData.value(7).toFloat()<<","<< getData.value(8).toFloat()<<","<< qLn(getData.value(7).toFloat())<<"\n";
    }
    getData.finish();
}

void Database::specificExport(QString fileName,QString SampleName,int rxnArea,int temp)
{
    //query to export all data;
    //select SampleName,temperature,replicantID,rxnTime,rxnArea,ln,T,stdDev from mydb.data join (mydb.trial, mydb.samples,mydb.temperatures) on (data.trialID=trial.idTrial and samples.idSamples = trial.sampleID and temperatures.idTemperatures= trial.temperatureid);
    QSqlQuery getData(db);
    getData.prepare("select SampleName,replicantID,temperature,rxnTime,rxnArea,ln,T,average,stdDev "
                    "from mydb.data join (mydb.trial, mydb.samples,mydb.temperatures) on "
                    "(data.trialID=trial.idTrial and samples.idSamples = trial.sampleID and temperatures.idTemperatures= trial.temperatureid) where samples.SampleName=? and temperatures.temperature=? and data.rxnArea=?;");
    getData.addBindValue(SampleName);

    getData.addBindValue(temp);
    getData.addBindValue(rxnArea);
    getData.exec();
    QFile file(fileName);
    if(file.open(QIODevice::ReadWrite)){
    QTextStream outputFile(&file);
    while(getData.next())
    {
        outputFile << getData.value(0).toString()<<","<< getData.value(1).toInt()<<","<< getData.value(2).toInt()<< ","<<getData.value(3).toFloat()<<","<< getData.value(4).toInt()<<","<< getData.value(5).toFloat()<<","<< getData.value(6).toFloat()<<","<< getData.value(7).toFloat()<<","<< getData.value(8).toFloat()<<","<< qLn(getData.value(7).toFloat())<<"\n";
    }
    }else
    {
        qDebug()<<"File Error";
    }

    getData.finish();
}
void Database::specificExport(QString fileName,QString SampleName,int rxnArea)
{
    //query to export all data;
    //select SampleName,temperature,replicantID,rxnTime,rxnArea,ln,T,stdDev from mydb.data join (mydb.trial, mydb.samples,mydb.temperatures) on (data.trialID=trial.idTrial and samples.idSamples = trial.sampleID and temperatures.idTemperatures= trial.temperatureid);
    QSqlQuery getData(db);
    getData.prepare("select SampleName,replicantID,rxnTemp,rxnTime,rxnArea,ln,T,average,stdDev "
                    "from mydb.data join (mydb.trial, mydb.samples) on "
                    "(data.trialID=trial.idTrial and samples.idSamples = trial.sampleID ) where samples.SampleName=? and data.rxnArea=?;");
    getData.addBindValue(SampleName);
    getData.addBindValue(rxnArea);
    getData.exec();
    QFile file(fileName);
    if(file.open(QIODevice::ReadWrite)){
    QTextStream outputFile(&file);
    while(getData.next())
    {
        outputFile << getData.value(0).toString()<<","<< getData.value(1).toInt()<<","<< getData.value(2).toInt()<< ","<<getData.value(3).toFloat()<<","<< getData.value(4).toInt()<<","<< getData.value(5).toFloat()<<","<< getData.value(6).toFloat()<<","<< getData.value(7).toFloat()<<","<< getData.value(8).toFloat()<<","<< qLn(getData.value(7).toFloat())<<"\n";
    }
    }else
    {
        qDebug()<<"File Error";
    }

    getData.finish();
}
