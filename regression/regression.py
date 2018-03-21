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
	y=1;
	for x in range(1,len(dataList)-1):
		print(dataList[x])
		lnList.append(float(dataList[y][6]))
		tList.append(float(dataList[y][9]))
		y +=1
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
