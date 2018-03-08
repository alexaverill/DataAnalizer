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
    QString username="";
    QString password="";
    QString host="";
    QString databaseName="";
};
#endif // LOCALSETTING_H
