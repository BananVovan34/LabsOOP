#include <fstream>
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <algorithm>

#include "politobjects.h"

// State

//
// Getters
//

const string State::get_name() { return name; };
const string State::get_capital() { return capital; };
const string State::get_government() { return government; };
const string State::get_language() { return language; };
const string State::get_religion() { return religion; };
const int State::get_area() { return area; };
const long long State::get_population() { return population; };
const string State::get_continent() { return continent; };

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

bool State::initFromFile(ifstream& infile) {
    if (infile >> name
        >> capital
        >> government
        >> language
        >> religion
        >> area
        >> population
        >> continent) return true;
    else return false;
}

//
// Operators
// 

bool State::operator==(const State& other) const {
    return name == other.name &&
        capital == other.capital &&
        government == other.government &&
        language == other.language &&
        religion == other.religion &&
        area == other.area &&
        population == other.population &&
        continent == other.continent;
}

bool State::operator!=(const State& other) const {
    return name != other.name &&
        capital != other.capital &&
        government != other.government &&
        language != other.language &&
        religion != other.religion &&
        area != other.area &&
        population != other.population &&
        continent != other.continent;
}

ostream& operator<<(ostream& os, State& state) {
    os << "| ��������: " << state.get_name() << endl;
    os << "| �������: " << state.get_capital() << endl;
    os << "| ����� ���������: " << state.get_government() << endl;
    os << "| ����: " << state.get_language() << endl;
    os << "| �������: " << state.get_religion() << endl;
    os << "| �������: " << state.get_area() << endl;
    os << "| ���������: " << state.get_population() << endl;
    os << "| ���������: " << state.get_continent() << endl;
    return os;
}

istream& operator>>(istream& is, State& state) {
    string name, capital, government, language, religion, continent;
    int area;
    long long population;

    cout << "\n[ ������� ] ������� �������� ��� ������ �������:" << endl;
    cout << "| ��������:" << endl;
    is.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(is, name);
    cout << "| �������:" << endl;
    getline(is, capital);
    cout << "| ����� ���������:" << endl;
    getline(is, government);
    cout << "| ����:" << endl;
    getline(is, language);
    cout << "| �������:" << endl;
    getline(is, religion);
    cout << "| �������:" << endl;
    is >> area;
    cout << "| ���������:" << endl;
    is >> population;
    is.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "| ���������:" << endl;
    getline(is, continent);

    state = State(name, capital, government, language, religion, area, population, continent);

    return is;
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
        << "| [ 1 ] ���������� ��������� ������� � ��������� ���������� �������� �������\n"
        << "| [ 2 ] ������� �� ����� �������� � ������� ������ �������� �� ����������� ��������� ������-�������� �����������\n"
        << "| [ 3 ] �������� ����� ������ � ������\n"
        << "| [ 4 ] ������� ������ �� ������\n"
        << "| [ 5 ] ����� �� ���������\n"
        << "[ ������� ] ����: ";
    cin >> action;

    if ((action <= 5) && (action >= 1)) {
        return action;
    }

    return -1;
}

// politObjects

//
// Getters
//

const int politObjects::get_objectsCount() { return objectsCount; };

//
// politObjects Methods
//

void politObjects::deleteRecord() {
    int INDEX;

    if (objectsCount <= 0) {
        cerr << "\n[ ������ ] � ������ �������� ����� ���� 1 ������, �� ��� �� ������ �������" << endl;
        return;
    }

    while (true) {
        cout << "\n[ ������� ] ������� ���������� ����� ���������� �������: " << endl;
        cin >> INDEX;
        INDEX--;

        if (INDEX < 0 || INDEX >= objectsCount) {
            cerr << "\n[ ������ ] �������� ������ ��� ��������! �������� ������ � �������� �� 1 �� " << objectsCount << endl;
        }
        else break;
    }

    politObject* politObject_STACK = new politObject[objectsCount - 1];
    for (int i = 0, j = 0; i < objectsCount; i++) {
        if (i != INDEX) politObject_STACK[j++] = objects[i];
    }

    delete[] objects;

    objects = politObject_STACK;
    objectsCount--;
}

void politObjects::calculationOfAmountOf(const string property, const string continentCondition) {
    if (property == "area") {
        int areaAmount = 0;

        for (int i = 0; i < objectsCount; i++)
        {
            if (continentCondition == objects[i].get_continent()) {
                areaAmount += objects[i].get_area();
            }
        }

        cout << "\n[ ����� ] ��������� ������� ���������� ���������� " << continentCondition << " ����� " << areaAmount << endl;
    }
    else if (property == "population") {
        long long populationAmount = 0;

        for (int i = 0; i < objectsCount; i++)
        {
            if (continentCondition == objects[i].get_continent()) {
                populationAmount += objects[i].get_population();
            }
        }

        cout << "\n[ ����� ] ��������� ��������� ���������� ���������� " << continentCondition << " ����� " << populationAmount << endl;
    }
    else {
        cerr << "\n\n[ ������ ] ������������ �������� " << property << endl;
    }
}

void politObjects::findMaxOf(const string property, const string languageCondition) {
    if (property == "area") {
        int maxIndex = -1;
        int areaMax = 0;

        for (int i = 0; i < objectsCount; i++)
        {
            if ((languageCondition == objects[i].get_language()) && (areaMax < objects[i].get_area())) {
                maxIndex = i;
                areaMax = objects[i].get_area();
            }
        }

        if (maxIndex != -1) {
            cout << "\n[ ����� ] ����� ������� �� ������� �����������, � �������� " << languageCondition
                << " - ��������������� ���� - " << objects[maxIndex].get_name() << ", �� �������� " << objects[maxIndex].get_capital() << endl;
        }
        else {
            cout << "\n[ ����� ] �� ������� ���������� � ������ " << languageCondition << endl;
        }
    }
    else if (property == "population") {
        int maxIndex = -1;
        long long populationMax = 0;

        for (int i = 0; i < objectsCount; i++)
        {
            if ((languageCondition == objects[i].get_language()) && (populationMax < objects[i].get_population())) {
                maxIndex = i;
                populationMax = objects[i].get_population();
            }
        }

        if (maxIndex != -1) {
            cout << "\n[ ����� ] ����� ������� �� ����������� ��������� �����������, � �������� " << languageCondition
                << " - ��������������� ���� - " << objects[maxIndex].get_name() << ", �� �������� " << objects[maxIndex].get_capital() << endl;
        }
        else {
            cout << "\n[ ����� ] �� ������� ���������� � ������ " << languageCondition << endl;
        }
    }
    else {
        cerr << "\n\n[ ������ ] ������������ �������� " << property << endl;
    }
}

politObjects::politObjects(const string FILE_PATH) {
    objectsCount = getStatesCount(FILE_PATH);

    if (objectsCount != -1) {
        objects = new State[objectsCount];

        ifstream infile(FILE_PATH);
        if (!infile.is_open()) {
            cerr << "\n\n[ ������ ] ������ �������� �����!" << endl;
            return;
        }

        infile.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int i = 0; i < objectsCount; i++) {
            objects[i].initFromFile(infile);
        }

        infile.close();
    }
    else {
        cerr << "\n[ ������ ] ������������ �������� numStates " << objectsCount << endl;
    }
}

politObjects::~politObjects() {
    delete[] objects;
}

//
// Operators
// 

politObjects& politObjects::operator+=(const State& newState) {
    politObject * newObjectsArray = new politObject[objectsCount + 1];
    for (int i = 0; i < objectsCount; ++i) {
        newObjectsArray[i] = objects[i];
    }
    newObjectsArray[objectsCount] = newState;
    delete[] objects;
    objects = newObjectsArray;
    ++objectsCount;
    return *this;
}

ostream& operator<<(ostream& os, politObjects& list) {
    int ITERATIONS = list.get_objectsCount();
    for (int i = 0; i < ITERATIONS; ++i) {
        os << "======================" << endl;
        os << "| ��������� �" << i + 1 << endl;
        os << list.objects[i];
        os << "======================" << endl << endl;
    }

    return os;
}

//
// Another Functions
//

void newRecord(politObjects& list) {
    State NEW_RECORD;
    cin >> NEW_RECORD;

    list += NEW_RECORD;
}