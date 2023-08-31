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


// int main() {
//     ifstream file;
//     file.open("india_data.csv");
//     string line;
//     getline(file, line);
//     while (getline(file, line)) {
//         cout << line << endl;
//     }
//     file.close();
//     return 0;
// }

int main()
{
    const int maxDataSize = 100;
    BankData data[maxDataSize];
    int dataSize = 0;
    ifstream file("india_data.csv");
    if (!file.is_open())
    {
        cerr << "Error occurred while opening the file." << endl;
        return 1;
    }
    string line;
    getline(file, line);
    int index = 0;
    while (getline(file, line))
    {
        char *char_array = new char[line.length() + 1];
        char_array[line.length()] = '\0';

        for (int i = 0; i < line.length(); i++)
        {
            char_array[i] = line[i];
        }
        // Returns first token
        char *token = strtok(char_array, ",");
        char *year = strtok(NULL, ",");
        int yearInt;
        sscanf(year, "%d", &yearInt);
        data[index].yearOfInvestment = yearInt;
        char *interestRate = strtok(NULL, ",");
        double interestRateDouble = stof(interestRate);
        data[index].rateOfInterest = interestRateDouble;
        char *inflation = strtok(NULL, ",");
        double inflationDouble = stof(inflation);
        data[index].rateOfInflation = inflationDouble;

        index++;
    }

    file.close();

    double investment, result = 0;
    int yearInvested;

    cout << "Enter the amount of investment: ";
    cin >> investment;
    cout << "Enter the year in which it was invested (after 1960): ";
    cin >> yearInvested;

    if (yearInvested < 1960)
    {
        cout << "Enter valid year of investment" << endl;
        return -1;
    }

    int originalAmount = investment;

    for (int i = 0; i < index; i++)
    {
        if (data[i].yearOfInvestment >= yearInvested)
        {
            investment = (investment * (1 + ((data[i].rateOfInterest - data[i].rateOfInflation) / 100.0)));
            result = investment;
        }
    }

    cout << "Money actually received: " << result << " INR" << endl;
    float amomuntWithInterest;
    float valueGained;
    for (int i = 0; i < index; i++)
    {
        if (data[i].yearOfInvestment == yearInvested)
        {
            amomuntWithInterest = (originalAmount * (1 + data[i].rateOfInterest / 100));
            valueGained = result - originalAmount;
            break;
        }
    }

    cout << "Value gained by the money after adding the interest of the investment year --> " << valueGained << " INR" << endl;

    return 0;
}