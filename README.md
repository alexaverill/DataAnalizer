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

The main point of work in the Data Input setp was to only read data that occured at a specific point of the Reaction Area. In our case this was every time the reaction area increased by 2%, essentially the goal was to pull data at 2%,4%,6%,...,98%, 100%. 

To find when we needed to record a data point the file was looped through and every row had its reaction area rounded to two decimal points and then compared to a target value. 
```
            float target = (float)place;
            float inVal = splitList.at(4).toFloat();
            float roundedVal = floor(inVal * 10)/10;
            //printf("%2f\n",roundedVal);
            if(roundedVal >= target){
                //insert into database.
                dP->rxnTime = splitList.at(0).toFloat();
                dP->rxnTemp = splitList.at(1).toFloat()+273.15;
                dP->rxnHeat = splitList.at(2).toFloat();
                dP->rxnRevCP = splitList.at(3).toFloat();
                dP->rxnArea = (int) target;
                dP->ln = qLn(dP->rxnTime);
                dP->T = (1/(dP->rxnTemp));

                db.insertData(dP);
                place+=2;
}
```
If the rounded value was greater or equal to the target value its rows were pushed into the Data Point Struct, the reaction temperature was incremented by 273.15 (to convert to Kelvin), the Natural Log of reaction temperature, and the inverse of reaction time were calculated and stored. Finally the data was pushed into the Database and stored. 

## Calculating Standard Deviation and Averages of Trials
The calculation of the Standard Deviation and the average of the trials is a user requested action that can be done after the required data has been entered. Once the user clicks the button they call setStdDev in the Database Class. setStdDev pulls a list of samples and temperatures, then loops through samples and for every temperature in that sample it will calculate the standard deviation at every percentage. 

SQL Query: 
```
update data set stdDev=(select * from(SELECT (sqrt(1/3)*pow(rxnTime-(select avg(rxnTime) as dev from trial left join(data) ON (trial.idtrial = data.trialID) where sampleID=? AND temperatureID=? and rxnArea=?),2)) from mydb.data where trialID=? and rxnArea=?) as x) where trialID=? and rxnArea=?"
```

Calculating the average follows the same pattern as the calculation of the Standard Deviation, the main reason that is is a seperate process was to simplify implementation to reach the required deadline for functional software. 
```
update data set average=(select avg(rxnTime) as dev  from trial join(SELECT * FROM data)as data ON (trial.idtrial = data.trialID) where sampleID=? AND temperatureID=? and rxnArea=?) where trialID=? and rxnArea=?")

```

## Exporting Data
Exporting data is teh exact oposite of the data inport, the end user will select a temperature, a compound, and a reaction aread and the matching data will be exported into a CSV file that can then be used in Linear Regression. The output data will have the following columns in the CSV:
```
SampleName,replicantID,temperature,rxnTime,rxnArea,ln,T,average,stdDev
```
The two main methods of export are to export based on Sample Name, Reaction Area, and Temperature, or to export based on Sample Name and Reaction Area for every temperature for that sample and area. 

## Linear Regression
The linear regression of this data was implemented using SciPy, Numpy, and the CSV libraries in python. Python was chosen due to the pre-existing and verified Linear Regression libraries that exist rather then trying to reinvent the wheel. The linear regression code can be found here: https://docs.scipy.org/doc/scipy-0.14.0/reference/generated/scipy.stats.linregress.html 
The only main changes in this program was the inclusion of importing the data from the outputted CSV file from the previous step.
## Helper SQL Scripts
After the initial development there was a few extra database operations that were needed to help with data processing. 
### Deleting Data
Data can be deleted based on the Sample Name as well as the Temperature. Edit the SampleName= or the Temperature = to delete specific data. 
First run this script to remove data in the data table:
```
delete from data where trialID in (select idTrial from trial where temperatureID=(select idTemperatures from temperatures where temperature=130) and SampleID=(select idSamples from samples where SampleName="Sigma"));
```

Then run this to clear data from the Trial Table:
```
delete from trial where temperatureID=(select idTemperatures from temperatures where temperature=130) and SampleID=(select idSamples from samples where SampleName="Sigma")
```
### Displaying Data
Display all data based on samplename, temperature and area
```
select * from mydb.trial join(mydb.data, mydb.temperatures, mydb.samples)
ON (trial.idtrial = data.trialID and trial.temperatureID = temperatures.idTemperatures and trial.sampleID = samples.idSamples)
where SampleName="Sigma" AND temperature=130 and rxnArea=2;
```
Get all by Sample Name and Temp:
```
select * from mydb.trial join(mydb.data, mydb.temperatures, mydb.samples)
ON (trial.idtrial = data.trialID and trial.temperatureID = temperatures.idTemperatures and trial.sampleID = samples.idSamples)
where SampleName="Sigma" AND temperature=130
```
Get all by sample:
```
select * from mydb.trial join(mydb.data, mydb.temperatures, mydb.samples)
ON (trial.idtrial = data.trialID and trial.temperatureID = temperatures.idTemperatures and trial.sampleID = samples.idSamples)
where SampleName="Sigma"
```
Get by Sample ordered by temperature:
```
select * from mydb.trial join(mydb.data, mydb.temperatures, mydb.samples)
ON (trial.idtrial = data.trialID and trial.temperatureID = temperatures.idTemperatures and trial.sampleID = samples.idSamples)
where SampleName="Sigma" order by temperatureID ASC
```
By Sample grouped by rxnArea
```
select * from mydb.trial join(mydb.data, mydb.temperatures, mydb.samples)
ON (trial.idtrial = data.trialID and trial.temperatureID = temperatures.idTemperatures and trial.sampleID = samples.idSamples)
where SampleName="Sigma" order by rxnArea ASC
```
Just get all data:
```
select * from mydb.trial join(mydb.data, mydb.temperatures, mydb.samples)
ON (trial.idtrial = data.trialID and trial.temperatureID = temperatures.idTemperatures and trial.sampleID = samples.idSamples) 
```
Selecting Data not at a temperature
```
select SampleName,replicantID,rxnTemp,rxnTime,rxnArea,ln,T,average,stdDev from mydb.data join (mydb.trial, mydb.samples,mydb.temperatures) on (data.trialID=trial.idTrial and samples.idSamples = trial.sampleID
and temperatures.idTemperatures= trial.temperatureid) where samples.SampleName="Sigma" and temperatures.temperature<>130 and data.rxnArea=2;
```
### Converting all data from Celcius to Kelvin 
One challenge was realizing that all data was in the wrong units for the initial inputs. To convert all that data to Kelvin this script could be used, also it could be used to convert it back to Celcius by subtracting the 273.15

```
UPDATE data set rxnTemp = rxnTemp+273.15
```
After the temperature is updated the Inverse of Temperature needs to be recalculated:
```
UPDATE data set T = 1/rxnTemp;
```

# Areas of Improvement
This project went fairly smoothly but as in every project there are areas of improvement. The first being extending the Data base class to not allow data duplication, currently it is possible to enter the same data twice. This would be the first issue to fix. Secondly it would be good to implement most of the SQL helper queries that are listed above into the User Interface to simplify the end users experiance. Along those same lines it would be good to implement a data viewer into the user interface to keep the user from having to use both this program as well as MYSQL workbench. 
