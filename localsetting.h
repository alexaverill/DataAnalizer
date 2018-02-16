#ifndef LOCALSETTING_H
#define LOCALSETTING_H
#include<QString>
class localsettings
{
public:
    QString returnUserName() {return username;}
    QString returnPassword() {return password;}
    QString returnHost() {return host;}
    QString returnDatabaseName() {return databaseName;}
    void setUserName(QString user){username=user;}
    void setPassword(QString pass){password=pass;}
    void setHostName(QString host){host=host;}
    void setDatabaseName(QString dbName){databaseName=dbName;}
private:
    QString username="root";
    QString password="averill";
    QString host="localhost";
    QString databaseName="mydb";
};
#endif // LOCALSETTING_H
