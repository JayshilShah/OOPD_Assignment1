#include <iostream>
#include <fstream>
#include <string.h>
#include <cmath>
#include <iomanip>

using namespace std;

struct BankData
{
    int yearOfInvestment;
    double rateOfInterest;
    double rateOfInflation;
};

const int maxDataSize = 100;
struct BankData dataOfInvestment[maxDataSize];
int index_of_array = 0;

void fileRead(){
    int dataSize = 0;
    ifstream file("spain_data.csv");
    if (!file.is_open())
    {
        cerr << "Error occurred while opening the file." << endl;
        return;
    }
    string line;
    getline(file, line);
    while (getline(file, line))
    {
        char *char_array = new char[line.length() + 1];
        char_array[line.length()] = '\0';

        for (int i = 0; i < line.length(); i++)
        {
            char_array[i] = line[i];
        }
        char *token = strtok(char_array, ",");
        char *year = strtok(NULL, ",");
        int yearInt;
        sscanf(year, "%d", &yearInt);
        dataOfInvestment[index_of_array].yearOfInvestment = yearInt;

        char *interestRate = strtok(NULL, ",");
        double interestRateDouble = stof(interestRate);
        dataOfInvestment[index_of_array].rateOfInterest = interestRateDouble;

        char *inflation = strtok(NULL, ",");
        double inflationDouble = stof(inflation);
        dataOfInvestment[index_of_array].rateOfInflation = inflationDouble;

        index_of_array++;
    }

    file.close();
}

void calculateValueOfAmount(double investedAmount, int investedYear){
    double amountInvested = investedAmount;
    double result = 0;
    double amountInEuro;
    if (investedYear < 1960 || investedYear >= 2023)
    {
        cout << "Enter valid year of investment" << endl;
        return;
    }
    for (int i = 0; i < index_of_array; i++)
    {
        if (dataOfInvestment[i].yearOfInvestment >= investedYear)
        {
            if(dataOfInvestment[i].yearOfInvestment == 2002){
                amountInEuro = (investedAmount / 166);
                investedAmount =  amountInEuro;
            }
            investedAmount = investedAmount + (investedAmount * ((dataOfInvestment[i].rateOfInterest - dataOfInvestment[i].rateOfInflation) / 100.0));
        }
    }
    result = investedAmount;
    double decimalPart = result - int(result);
    int cent = int(decimalPart*100);
    cout << "Money actually received: " << int(result) << " Euroes and " << cent << " cent" << endl;
    float amomuntWithInterest;
    float valueGained;
    for (int i = 0; i < index_of_array; i++)
    {
        if (dataOfInvestment[i].yearOfInvestment == investedYear)
        {
            amomuntWithInterest = amountInvested + (amountInvested * ((dataOfInvestment[i].rateOfInterest - dataOfInvestment[i].rateOfInflation) / 100));
            if(investedYear < 2002){
                amomuntWithInterest = (amomuntWithInterest / 166);
            }
            valueGained = result - amomuntWithInterest;
            break;
        }
    }
    double decimalPart1 = valueGained - int(valueGained);
    int cent1 = int(decimalPart1*100);
    cout << "Value gained after the year of invesment till now: " << int(valueGained) << " Euroes and " << abs(cent1) << " cent" << endl;

    double invest = 1000.00; 
    double dictatoral = invest;
    double monarchy = invest;
    for(int i = 1; i <= index_of_array; i++){
        if (dataOfInvestment[i].yearOfInvestment >= 1967 && dataOfInvestment[i].yearOfInvestment <= 1977){
            dictatoral = dictatoral + (dictatoral * ((dataOfInvestment[i].rateOfInterest - dataOfInvestment[i].rateOfInflation) / 100.0));
        }
        if (dataOfInvestment[i].yearOfInvestment >= 1977 && dataOfInvestment[i].yearOfInvestment <= 1987){
            monarchy = monarchy + (monarchy * ((dataOfInvestment[i].rateOfInterest - dataOfInvestment[i].rateOfInflation) / 100.0));
        }
    }
    if(dictatoral > monarchy){
        cout << "The value of money grew faster during the dictatorial era than the republican era." << endl;
    }
    else if(monarchy > dictatoral){
        cout << "The value of money grew faster during the republican era than the dictatorial era." << endl;
    }
}

int main()
{    
    fileRead();
    double investment;
    int investedYear;
    cout << "Enter the amount of investment (before 2002 in Peseta, after 2002 in Euroes): ";
    cin >> investment;
    cout << "Enter the year of investment (after 1960): ";
    cin >> investedYear;
    calculateValueOfAmount(investment, investedYear);   

    return 0;
}