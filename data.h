#ifndef DATA_H
#define DATA_H
#include<QString>
#include "datapoint.h"
class Data
{
public:
    Data();
    Data(QString);
    int percision = .05; //this will be added to a value and compared to make sure it is in range.
    int percentChange = 2;
    QString filePath; // file path of file to process.
    void processFile(dataPoint *);
    void setFile(QString filePath);
};

#endif // DATA_H
