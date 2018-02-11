#ifndef DATAPOINT_H
#define DATAPOINT_H

struct dataPoint
{
    int trial; //trial number from UI
    int temperature;//from UI
    QString compound; //returns ID of a compound
    //pulled from data;
    float rxnTime;
    float rxnTemp;
    float rxnHeat;
    float rxnRevCP;
    float rxnArea;

};

#endif // DATAPOINT_H
