#include "states.h"
#include <fstream>
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <algorithm>

using namespace std;
// State
//
// Getters
//
string State::get_name() { return name; };
string State::get_capital() { return capital; };
string State::get_government() { return government; };
string State::get_language() { return language; };
string State::get_religion() { return religion; };
int State::get_area() { return area; };
long long State::get_population() { return population; };
string State::get_continent() { return continent; };
//
// Setters
//
void State::set_name(string VALUE) { name = VALUE; };
void State::set_capital(string VALUE) { capital = VALUE; };
void State::set_government(string VALUE) { government = VALUE; };
void State::set_language(string VALUE) { language = VALUE; };
void State::set_religion(string VALUE) { religion = VALUE; };
void State::set_area(int VALUE) { area = VALUE; };
void State::set_population(long long VALUE) { population = VALUE; };
void State::set_continent(string VALUE) { continent = VALUE; };
//
// Consructors
//
State::State() {
    name = "";
    capital = "";
    government = "";
    language = "";
    religion = "";
    area = 0;
    population = 0;
    continent = "";
};

State::State(string set_name, string set_capital, string set_government, string set_language, string set_religion, int set_area, long long set_population, string set_continent) {
    name = set_name;
    capital = set_capital;
    government = set_government;
    language = set_language;
    religion = set_religion;
    area = set_area;
    population = set_population;
    continent = set_continent;
}

State::State(const State& STACK) {
    name = STACK.name;
    capital = STACK.capital;
    government = STACK.government;
    language = STACK.language;
    religion = STACK.religion;
    area = STACK.area;
    population = STACK.population;
    continent = STACK.continent;
}
//
// Methods
//
void State::print() {
    cout << "| ��������: " << name << endl;
    cout << "| �������: " << capital << endl;
    cout << "| ����� ���������: " << government << endl;
    cout << "| ����: " << language << endl;
    cout << "| �������: " << religion << endl;
    cout << "| �������: " << area << endl;
    cout << "| ���������: " << population << endl;
    cout << "| ���������: " << continent << endl;
}

bool State::initFromFile(ifstream& infile) {
    if (infile >> name
        >> capital
        >> government
        >> language
        >> religion
        >> area
        >> population
        >> continent) return true;
    else false;
}
//
// listStates Methods
//
void listStates::newRecord() {
    State* STATES_STACK = new State[countStates + 1];
    for (int i = 0; i < countStates; i++) {
        STATES_STACK[i] = states[i];
    }

    string name, capital, government, language, religion, continent;
    int area;
    long long population;

    cout << "\n[ ������� ] ������� �������� ��� ������ �������:" << endl;
    cout << "| ��������:" << endl;
    cin.ignore();
    getline(cin, name);
    cout << "| �������:" << endl;
    getline(cin, capital);
    cout << "| ����� ���������:" << endl;
    getline(cin, government);
    cout << "| ����:" << endl;
    getline(cin, language);
    cout << "| �������:" << endl;
    getline(cin, religion);
    cout << "| �������:" << endl;
    cin >> area;
    cout << "| ���������:" << endl;
    cin >> population;
    cin.ignore();
    cout << "| ���������:" << endl;
    getline(cin, continent);

    STATES_STACK[countStates] = State(name, capital, government, language, religion, area, population, continent);
    delete[] states;

    states = STATES_STACK;
    countStates++;
}

void listStates::deleteRecord() {
    int INDEX;

    if (countStates <= 0) {
        cerr << "\n[ ������ ] � ������ �������� ����� ���� 1 ������, �� ��� �� ������ �������" << endl;
        return;
    }

    while (true) {
        cout << "\n[ ������� ] ������� ���������� ����� ���������� �������: " << endl;
        cin >> INDEX;
        INDEX--;

        if (INDEX < 0 || INDEX >= countStates) {
            cerr << "\n[ ������ ] �������� ������ ��� ��������! �������� ������ � �������� �� 1 �� " << countStates << endl;
        }
        else break;
    }

    State* STATES_STACK = new State[countStates - 1];
    for (int i = 0, j = 0; i < countStates; i++) {
        if (i != INDEX) STATES_STACK[j++] = states[i];
    }

    delete[] states;

    states = STATES_STACK;
    countStates--;
}

void listStates::calculationOfAmountOf(const string property, const string continentCondition) {
    if (property == "area") {
        int areaAmount = 0;

        for (int i = 0; i < countStates; i++)
        {
            if (continentCondition == states[i].get_continent()) {
                areaAmount += states[i].get_area();
            }
        }

        cout << "\n[ ����� ] ��������� ������� ���������� ���������� " << continentCondition << " ����� " << areaAmount << endl;
    }
    else if (property == "population") {
        long long populationAmount = 0;

        for (int i = 0; i < countStates; i++)
        {
            if (continentCondition == states[i].get_continent()) {
                populationAmount += states[i].get_population();
            }
        }

        cout << "\n[ ����� ] ��������� ��������� ���������� ���������� " << continentCondition << " ����� " << populationAmount << endl;
    }
    else {
        cerr << "\n\n[ ������ ] ������������ �������� " << property << endl;
    }
}

void listStates::findMaxOf(const string property, const string languageCondition) {
    if (property == "area") {
        int maxIndex = -1;
        int areaMax = 0;

        for (int i = 0; i < countStates; i++)
        {
            if ((languageCondition == states[i].get_language()) && (areaMax < states[i].get_area())) {
                maxIndex = i;
                areaMax = states[i].get_area();
            }
        }

        if (maxIndex != -1) {
            cout << "\n[ ����� ] ����� ������� �� ������� �����������, � �������� " << languageCondition
                << " - ��������������� ���� - " << states[maxIndex].get_name() << ", �� �������� " << states[maxIndex].get_capital() << endl;
        }
        else {
            cout << "\n[ ����� ] �� ������� ���������� � ������ " << languageCondition << endl;
        }
    }
    else if (property == "population") {
        int maxIndex = -1;
        long long populationMax = 0;

        for (int i = 0; i < countStates; i++)
        {
            if ((languageCondition == states[i].get_language()) && (populationMax < states[i].get_population())) {
                maxIndex = i;
                populationMax = states[i].get_population();
            }
        }

        if (maxIndex != -1) {
            cout << "\n[ ����� ] ����� ������� �� ����������� ��������� �����������, � �������� " << languageCondition
                << " - ��������������� ���� - " << states[maxIndex].get_name() << ", �� �������� " << states[maxIndex].get_capital() << endl;
        }
        else {
            cout << "\n[ ����� ] �� ������� ���������� � ������ " << languageCondition << endl;
        }
    }
    else {
        cerr << "\n\n[ ������ ] ������������ �������� " << property << endl;
    }
}

listStates::listStates(const string FILE_PATH) {
    countStates = getStatesCount(FILE_PATH);

    if (countStates != -1) {
        states = new State[countStates];
        
        ifstream infile(FILE_PATH);
        if (!infile.is_open()) {
            cerr << "\n\n[ ������ ] ������ �������� �����!" << endl;
            return;
        }

        infile.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int i = 0; i < countStates; i++) {
            states[i].initFromFile(infile);
        }

        infile.close();
    }
    else {
        cerr << "\n[ ������ ] ������������ �������� numStates " << countStates << endl;
    }
}

listStates::~listStates() {
    delete[] states;
}

void listStates::dataOutput() {
    for (int i = 0; i < countStates; ++i) {
        cout << "======================" << endl;
        cout << "| ��������� �" << i + 1 << endl;
        states[i].print();
        cout << "======================" << endl << endl;
    }
}
//
// Another Functions
//
int getStatesCount(const string FILE_PATH) {
    ifstream infile(FILE_PATH);
    if (!infile.is_open()) {
        cerr << "\n\n[ ������ ] ������ �������� �����!" << endl;
        return -1;
    }

    int COUNT;
    infile >> COUNT;
    infile.close();

    return COUNT;
}

int getUserAction() {
    int action;
    cout << "\n[ ������� ] �������� ��������:\n"
        << "| 1. ���������� ��������� ������� � ��������� ���������� �������� �������\n"
        << "| 2. ������� �� ����� �������� � ������� ������ �������� �� ����������� ��������� ������-�������� �����������\n"
        << "| 3. �������� ����� ������ �� ������\n"
        << "| 4. ������� ������ �� ������\n"
        << "| 5. ����� �� ���������\n"
        << "[ ������� ] ����: ";
    cin >> action;

    if ((action <= 5) && (action >= 1)) {
        return action;
    }

    return -1;
}