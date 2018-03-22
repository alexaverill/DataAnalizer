# DataAnalyzer
Simple GUI program to allow for data processig and manipulation. 
This was designed for a chemistry research project in order to break down collected data files.The main purpose was to simplify and speed up data processing to avoid manually having to clean files and perform calculations. 

# Requirements
The software shall read in a data file 

The software shall process that data file and extract data whenever the reaction area is an even number

An even number is defined as between 2 and 100 inclusive (i.e. {2,4,6,8,...98,99,100})

The software shall use the first reaction area that is equal to or greater then the even number

The software shall calculate ln(reaction Time)

The software shall calculate (ln(1/reaction temp))

The software shall store all data that it extracts

The software shall allow for exporting of data into a CSV file

The software shall allow for exporting based on reaction area

The software shall allow for exporting based on reaction temperature

The software shall allow for exporting based on compounds

The software shall be able to calculate standard deviation of data

The software shall calculate standard deviation based on a samples trials at a percentage

(I.e the standard deviation of the 3 trials for Compound A at 2% of a reaction) 

The software shall be able to calculate average values for data

The software shall have a user interface to facilitate data entry and export

The software shall be able to preform linear regression based on input data

# Software Architecture
The software architecture for this system is fairly simple, essentially it is an object oriented client server architecture. The client is the user interface that is used to enter and export the data, with the server being the MYSQL database that stores the data. 
## Technologies
This software is build using QT Widgets and C++ for the user interface, and uses a Mysql database for data storage.All C++ software was written using QT Creator and QT 5.10.0
Additionally it uses python with numpy and scipy as well as the csv libaries to complete the linear regression.
# Database Design
The database design for this software is fairly simple, all data in this system is relational. 

![Database Diagram](https://raw.githubusercontent.com/alexaverill/DataAnalyzer/databaseDiagram.PNG)
The main relations in the data are each individual row of data is related to a Compound, a Temperature and a Trial. Due to this the database was broken down into a Samples and Temperatures table, a trial table that maps a Temperature and Sample to a trial, and then a data table which is an individual row of data mapped to a trial. 


# Software Implementation
This software was implemented in QT Creator usign QT 5.10.0 and QT widgets. The main user interface was constructed out of QT widgets to provide a simple way for the end user to enter trials, calculate standard deviation and calculate the average values of trials. 

## Data Input
Data input into this program was a two part process, first the user had to define the Trial, Temperature, Sample and Data File in the User Interface. Then the program would take that input and being to processes the input data file. 
In order to store the data a custom Data Point struct was created to hold the data that was read from the file as well as the data input by the user. 
```

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
```

The main point of work in the Data Input setp was to only read data that occured at a specific point of the Reaction Area. In our case this was every time the reaction area increased by 2%. To find when we needed to record a data point the file was looped through and every row had its reaction area rounded to two decimal points and then compared to a target value. If the rounded value was greater or equal to the target value it was stored in the database, and then the target value was incremeted by 2. 
Additionally the Natural Log of reaction time and the inverse of the reaction temperature were calculated prior to the data being stored in the databsase. 

## Calculating Standard Deviation and Averages of Trials

## Exporting Data

## Linear Regression

## Helper SQL Scripts

# Testing
