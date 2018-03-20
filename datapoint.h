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
    int rxnArea;
    float ln; // calculated from LN(rxnTemp)
    float T; // calculated as LN(1/rxnTime).

};

#endif // DATAPOINT_H
