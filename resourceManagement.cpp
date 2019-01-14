#ifndef RESOURCEMANAGEMENT_H_
#include "resourceManagement.h"
#endif // RESOURCEMANAGEMENT_H_

int students = 30;
int timeBegin = 9;
int timeEnd = 16;

float costWater = 500;
float costElectricity = 1200;
float costGas = 200;
float monthlyBudget = 2500;
float lastYearAverageWater = 500;
float lastYearAverageElectricity = 1150;
float lastYearAverageGas = 175;
float lastYearAverageCulture = 675;
float historyByMonth[12] = {2000,1900,2200,1700,2100,2400,1000,1200,1700,2000,2100,1600};

//Computes cultural budget
float getCulturalBudget() {
    return monthlyBudget-totalPerMonth();
}

//Computes hours in a month
int hoursInAMonth() {
    return (timeEnd-timeBegin)*30;
}

float getBiggestBill() {
    float bills[4] = {costElectricity,costGas,costWater,getCulturalBudget()};
    float temp;
    for(int i = 0; i < 4; i++) {
        if (bills[i] > temp) {
            temp = bills[i];
        }
    }
    return temp;
}

//Computes the electricity per student and per hour indicator
float electricityPerStudentPerHour() {
    return costElectricity/students/hoursInAMonth();
}


//Computes the total cost per student indicator
float totalCostsPerStudentPerMonth() {
    return totalPerMonth()/students;
}

//Computes the costs per day from the bills
float totalPerDay() {
    return totalPerMonth()/30;
}

//Computes the costs per month from the bills
float totalPerMonth() {
    return costElectricity+costGas+costWater;
}

//Returns the highest budget from the history for a pretty graph
float getHighestBudget() {
    float temp = 0.0;
    for(int i = 0; i < 12;i++) {
        if (historyByMonth[i] > temp) {
            temp = historyByMonth[i];
        }
    }
    return temp;
}

void computeAverages() {
    float total = 0;

    for(int i = 0; i < 12; i++) {
        total += historyByMonth[i];
    }
    total = total/12;
    lastYearAverageElectricity = total*0.6;
    lastYearAverageWater = total*0.28;
    lastYearAverageGas = total*0.12;
    lastYearAverageCulture = monthlyBudget-(lastYearAverageElectricity+lastYearAverageWater+lastYearAverageGas);
}

//Writes the data to a save file written as a CSV
void writeToCsv() {
    ofstream saveFile;
    saveFile.open("data.sav", ios::out | ios::trunc);
    if (saveFile.is_open()){
        saveFile << "Students " << students << "\n";
        saveFile << "timeBegin " << timeBegin << "\n";
        saveFile << "timeEnd " << timeEnd << "\n";
        saveFile << "costElectricity " << costElectricity << "\n";
        saveFile << "costGas " << costGas << "\n";
        saveFile << "costWater " << costWater << "\n";
        saveFile << "historyByMonth :" << "\n";
        for (int i = 0; i < 12; i++) {
            saveFile << historyByMonth[i];
            if (i < 11) {
                saveFile << ",";
            }
        }
        saveFile << "\n";
        saveFile.close();
    } else {
        cout << "Unable to open the file" << endl;
    }
}


//Reads the data from a save file written as a CSV
void getFromCsv() {
    string studentsString, timeBeginString, timeEndString, costElectricityString, costGasString, costWaterString, historyByMonthString;
    ifstream saveFile;
    saveFile.open("data2.sav");
    if (saveFile.is_open()){
        getline(saveFile, studentsString);
        students = atoi(stringSplitter(studentsString).c_str());
        /*string tada = stringSplitter(studentsString);
        ofstream testFile;
        testFile.open("data3.sav", ios::out | ios::trunc);
        testFile << tada << "\n";
        testFile.close();*/
        getline(saveFile, timeBeginString);
        timeBegin = atoi(stringSplitter(timeBeginString).c_str());
        getline(saveFile, timeEndString);
        timeEnd = atoi(stringSplitter(timeEndString).c_str());
        getline(saveFile, costElectricityString);
        costElectricity = atof(stringSplitter(costElectricityString).c_str());
        getline(saveFile, costGasString);
        costGas = atof(stringSplitter(costGasString).c_str());
        getline(saveFile, costWaterString);
        costWater = atof(stringSplitter(costWaterString).c_str());
        getline(saveFile, historyByMonthString);//Useless line in the file saver
        getline(saveFile, historyByMonthString);
        size_t pos = 0;
        int i = 0;
        while ((pos = historyByMonthString.find(",")) != string::npos) {
            historyByMonth[i] = atoi(historyByMonthString.substr(0, pos).c_str());
            historyByMonthString.erase(0, pos + 1);
            i++;
        }
        historyByMonth[11] = atoi(historyByMonthString.substr(0, pos).c_str());
        saveFile.close();
        computeAverages();
    } else {
        cout << "Unable to open the file" << endl;
    }
}

string stringSplitter(string s) {
    size_t pos = 0;
    while ((pos = s.find(" ")) != string::npos) {
            s.erase(0, pos + 1);
            s = s.substr(0, pos);
    }
    return s;
}
