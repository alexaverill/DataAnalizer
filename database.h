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
    //~Database();
    bool insertData(dataPoint *);
    bool connect();
    void close();
    std::stack<QString> returnTrials();
    QStringList returnTemperatures();
    QStringList returnSamples();
    int getSampleID(QString compoundName);
    int getTempID(int temp);
    float calculateAvg(int sampleID, int temp, int areaVal);

    QList<int> returnTempID();
    QList<int> returnSampleID();
    void setStdDev();
    void generalExport(QString fileName);

    void specificExport(QString fileName, QString SampleName, int rxnArea, int temp);
private:
    QSqlDatabase db;
    bool dbOpen = false;
};

#endif // DATABASE_H
