#ifndef DATABASE_H
#define DATABASE_H
#include<QString>
#include<QSql>
#include<QSqlDatabase>
#include "datapoint.h"
#include<stack>

class Database
{
public:
    Database();
    bool insertData(dataPoint *);
    bool connect();
    void close();
    std::stack<QString> returnTrials();
    QStringList returnTemperatures();
    QStringList returnSamples();
    int getSampleID(QString compoundName);
    int getTempID(int temp);
private:
    QString username="root";
    QString password="averill";
    QString host="localhost";
    QString databaseName="mydb";

    QSqlDatabase db;
    bool dbOpen = false;
};

#endif // DATABASE_H
