#ifndef RESOURCEMANAGEMENT_H_
#define RESOURCEMANAGEMENT_H_

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>


using namespace std;

//Definition of the values
extern int students;

//Hours of the day
extern int timeBegin;
extern int timeEnd;

//Bill by month in euros
extern float costWater;
extern float costElectricity;
extern float costGas;
extern float monthlyBudget;
extern float lastYearAverageWater;
extern float lastYearAverageElectricity;
extern float lastYearAverageGas;
extern float lastYearAverageCulture;

extern float historyByMonth[12];

int hoursInAMonth();
float electricityPerStudentPerHour();
float totalCostsPerStudentPerMonth();
float totalPerDay();
float totalPerMonth();
float getHighestBudget();
float getCulturalBudget();
float getBiggestBill();
void computeAverages();
void writeToCsv();
void getFromCsv();
string stringSplitter(string s);

#endif
