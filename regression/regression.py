from scipy import stats
import numpy as np
import csv
while True:
	fileIn = input("Enter csv file path:")
# scipy regression library https://docs.scipy.org/doc/scipy-0.14.0/reference/generated/scipy.stats.linregress.html  
	with open(fileIn,'r') as f:
	    reader = csv.reader(f)
	    dataList = list(reader)
	#print(dataList)
	print(len(dataList))
	lnList = []
	tList = []
	x=0;
	for element in dataList:
	    lnList.append(float(dataList[x][6]))
	    tList.append(float(dataList[x][9]))
	    x +=1
	print(lnList);
	print(tList);
	y = np.array(lnList)
	x = np.array(tList)
	slope, intercept, r_value, p_value, std_err = stats.linregress(x,y)
	print("Slope: ", slope)
	print("Intercept: ",intercept)
	print("R Value: ", r_value)
	print("R^2 Value: ", r_value**2)
	print("P Value: ", p_value)
	print("standard error: ", std_err)
