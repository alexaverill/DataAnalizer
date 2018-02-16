#include "data.h"
#include "datapoint.h"
#include<QDebug>
#include<QFile>
#include<QtMath>
#include <database.h>
Data::Data()
{
    qDebug() << "Entering Data Class";
}
Data::Data(QString fileIn)
{
    qDebug() << "Entering Data Class with "+fileIn;
    setFile(fileIn);

}
void Data::setFile(QString fileIn)
{
    filePath = fileIn;
    return;
}
void Data::processFile(dataPoint *dP)
{
    Database db;
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return;
    }
    bool header = true;
    int place = 2;
    QTextStream in(&file);
    while(!in.atEnd())
    {
        QString line =in.readLine();
        if(!header) // checking to see if the data in is part of the header, if it is we dont want to do anything on it.
        {
            QStringList splitList = line.split('\t'); //data is seperated by tabs.
            /*
             *
               0     Sig1	Time (min)
               1     Sig2	Temperature (°C)
               2     Sig3	Heat Flow (mW)
               3     Sig4	Rev Cp (mJ/°C)
               4     Sig5	Area percent (%)
                */
            //Per the requirements we are looking for the even percentage values. i.e 2%,4%,6% etc.
            //we also need to make sure that it is within the range.
            //the data is in what is essentially a float. So we need to take in the values and round to two decimal points.
            float target = (float)place;
            float inVal = splitList.at(4).toFloat();
            float roundedVal = floor(inVal * 10)/10;
            //printf("%2f\n",roundedVal);
            if(roundedVal == target){
                //insert into database.
                dP->rxnTime = splitList.at(0).toFloat();
                dP->rxnTemp = splitList.at(1).toFloat();
                dP->rxnHeat = splitList.at(2).toFloat();
                dP->rxnRevCP = splitList.at(3).toFloat();
                dP->rxnArea = (int) target;
                dP->ln = qLn(dP->rxnTime);
                dP->T = (1/dP->rxnTemp);

                db.insertData(dP);
                place+=2;
            }
        }
        if(line.contains("StartOfData")) //the header ends with this line so we can turn the header to false and will start on actual data the next run through the loop.
        {
            header = false;
        }
    }
    //db.close();
   // db.~Database();
    //qDebug() << dP->trial;
}
