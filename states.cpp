#include "states.h"
#include <fstream>
#include <iostream>
#include <string>
#include <limits>
#include <vector>

using namespace std;

int getStatesCount(string FILE_PATH) {
    ifstream infile(FILE_PATH);
    if (!infile.is_open()) {
        cerr << "[ ������ ] ������ �������� �����!" << endl;
        return -1;
    }

    int COUNT;
    infile >> COUNT;
    infile.close();

    return COUNT;
}

void readingFromFile(State* states, int numStates, string FILE_PATH) {

    ifstream infile(FILE_PATH);
    if (!infile.is_open()) {
        cerr << "[ ������ ] ������ �������� �����!" << endl;
        return;
    }

    infile.ignore(numeric_limits<streamsize>::max(), '\n');


    for (int i = 0; i < numStates; i++) {
        infile >> states[i].name
            >> states[i].capital
            >> states[i].government
            >> states[i].language
            >> states[i].religion
            >> states[i].area
            >> states[i].population
            >> states[i].continent;
    }

    infile.close();
}

void calculationOfAmountOf(State * states, int numStates, string property, string continentCondition) {
    if (property == "area") {
        int areaAmount = 0;

        for (int i = 0; i < numStates; i++)
        {
            if (continentCondition == states[i].continent) {
                areaAmount += states[i].area;
            }
        }

        cout << "��������� ������� ���������� ���������� " << continentCondition << " ����� " << areaAmount << endl;
    }
    else if (property == "population") {
        long long populationAmount = 0;

        for (int i = 0; i < numStates; i++)
        {
            if (continentCondition == states[i].continent) {
                populationAmount += states[i].population;
            }
        }

        cout << "��������� ��������� ���������� ���������� " << continentCondition << " ����� " << populationAmount << endl;
    }
    else {
        cerr << "[ ������ ] ������������ �������� " << property << endl;
    }
}

void findMaxOf(State* states, int numStates, string property, string languageCondition) {
    if (property == "area") {
        int maxIndex = -1;
        int areaMax = 0;

        for (int i = 0; i < numStates; i++)
        {
            if ((languageCondition == states[i].language) && (areaMax < states[i].area)) {
                maxIndex = i;
                areaMax = states[i].area;
            }
        }

        if (maxIndex != -1) {
            cout << "����� ������� �� ������� �����������, � �������� " << languageCondition
                << " - ��������������� ���� - " << states[maxIndex].name << ", �� �������� " << states[maxIndex].capital << endl;
        }
        else {
            cout << "�� ������� ���������� � ������ " << languageCondition << endl;
        }
    }
    else if (property == "population") {
        int maxIndex = -1;
        long long populationMax = 0;

        for (int i = 0; i < numStates; i++)
        {
            if ((languageCondition == states[i].language) && (populationMax < states[i].population)) {
                maxIndex = i;
                populationMax = states[i].population;
            }
        }

        if (maxIndex != -1) {
            cout << "����� ������� �� ����������� ��������� �����������, � �������� " << languageCondition
                << " - ��������������� ���� - " << states[maxIndex].name << ", �� �������� " << states[maxIndex].capital << endl;
        }
        else {
            cout << "�� ������� ���������� � ������ " << languageCondition << endl;
        }
    }
    else {
        cerr << "[ ������ ] ������������ �������� " << property << endl;
    }
}

void dataOutput(State * states, int numStates) {
    for (int i = 0; i < numStates; ++i) {
        cout << "======================" << endl;
        cout << "��������: " << states[i].name << endl;
        cout << "�������: " << states[i].capital << endl;
        cout << "����� ���������: " << states[i].government << endl;
        cout << "����: " << states[i].language << endl;
        cout << "�������: " << states[i].religion << endl;
        cout << "�������: " << states[i].area << endl;
        cout << "���������: " << states[i].population << endl;
        cout << "���������: " << states[i].continent << endl << endl;
    }
}