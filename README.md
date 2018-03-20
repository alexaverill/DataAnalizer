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
The database design for this software is fairly simple, all data in this system is relational. The main relational breakdown  is that each row of data from the input file has a Compound, a Temperature, and a Trial.  The Compounds and temperatures are all predefined and  unchanging so they were given their own tables in order to limit data duplication. The trial table is created as data is entered and will store a trial id to reference a row of the input data as well as the compound and temperature id to reference the compounds and temperature tables. 


# Software Implementation

# Testing
