#include <fstream>
#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <typeinfo>

#include "politobjects.h"

using namespace std;

// PolitObject
const string politObject::get_name() { return name; };
const int politObject::get_area() { return area; };
const long long politObject::get_population() { return population; };
const string politObject::get_continent() { return continent; };

bool politObject::initFromFile(ifstream& infile) { return true; };

// City
const string City::get_state() { return state; };
const string City::get_mayor() { return mayor; };
const long long City::get_budget() { return budget; };
const bool City::get_isCapital() { return isCapital; };

bool City::initFromFile(ifstream& infile) {
    string isCapitalStr;

    if (infile >> name
        >> state
        >> mayor
        >> budget
        >> area
        >> population
        >> isCapitalStr
        >> continent) {
        isCapital = stringToBool(isCapitalStr);
        return true;
    }
    else {
        return false;
    }
}

City::City() {};
City::City(string set_name, bool set_isCapital, string set_state, string set_mayor, long long set_budget, int set_area, long long set_population, string set_continent) {
    name = set_name;
    isCapital = set_isCapital;
    state = set_state;
    mayor = set_mayor;
    budget = set_budget;
    area = set_area;
    population = set_population;
    continent = set_continent;
}

ostream& operator<<(ostream& os, City& city) {
    os << "\n| ��������: " << city.get_name() << endl;
    os << "| �������: " << boolToString(city.get_isCapital()) << endl;
    os << "| ������: " << city.get_state() << endl;
    os << "| ���: " << city.get_mayor() << endl;
    os << "| ������: " << city.get_budget() << endl;
    os << "| �������: " << city.get_area() << endl;
    os << "| ���������: " << city.get_population() << endl;
    os << "| ���������: " << city.get_continent() << endl;
    return os;
}

istream& operator>>(istream& is, City& city) {
    string name, isCapital, state, mayor, continent;
    int area;
    long long population, budget;

    cout << "\n[ ������� ] ������� �������� ��� ������ �������:" << endl;
    cout << "| ��������:" << endl;
    is.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(is, name);
    cout << "| ������� (+ ��� -):" << endl;
    getline(is, isCapital);
    cout << "| ������:" << endl;
    getline(is, state);
    cout << "| ���:" << endl;
    getline(is, mayor);
    cout << "| ������:" << endl;
    is >> budget;
    cout << "| �������:" << endl;
    is >> area;
    cout << "| ���������:" << endl;
    is >> population;
    is.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "| ���������:" << endl;
    getline(is, continent);

    city = City(name, stringToBool(isCapital), state, mayor, budget, area, population, continent);

    return is;
}

// State
const string State::get_capital() { return capital; }
const string State::get_government() { return government; }
const string State::get_language() { return language; }
const string State::get_religion() { return religion; }

void State::set_name(string VALUE) { name = VALUE; }
void State::set_capital(string VALUE) { capital = VALUE; }
void State::set_government(string VALUE) { government = VALUE; }
void State::set_language(string VALUE) { language = VALUE; }
void State::set_religion(string VALUE) { religion = VALUE; }
void State::set_area(int VALUE) { area = VALUE; }
void State::set_population(long long VALUE) { population = VALUE; }
void State::set_continent(string VALUE) { continent = VALUE; }

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

State::State() {}

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

bool State::operator==(const State& other) const {
    return (name == other.name && capital == other.capital && government == other.government && language == other.language && religion == other.religion && area == other.area && population == other.population && continent == other.continent);
}

bool State::operator!=(const State& other) const {
    return !(*this == other);
}

ostream& operator<<(ostream& os, State& state) {
    os << "\n| ������: " << state.name << endl;
    os << "| �������: " << state.capital << endl;
    os << "| ����� ���������: " << state.government << endl;
    os << "| ����: " << state.language << endl;
    os << "| �������: " << state.religion << endl;
    os << "| �������: " << state.area << endl;
    os << "| ���������: " << state.population << endl;
    os << "| ���������: " << state.continent << endl;
    return os;
}

istream& operator>>(istream& is, State& state) {
    string name, capital, government, language, religion, continent;
    int area;
    long long population;

    cout << "\n[ ������� ] ������� �������� ��� ������ �������:" << endl;
    cout << "| ��������:" << endl;
    is.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the leftover newline character from previous input
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
    is.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the leftover newline character from previous input
    cout << "| ���������:" << endl;
    getline(is, continent);

    state = State(name, capital, government, language, religion, area, population, continent);

    return is;
}

// politObjects
const int politObjects::get_objectsCount() { return objectsCount; };

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
        else {
            break;
        }
    }

    delete objects[INDEX];

    for (int i = INDEX; i < objectsCount - 1; i++) {
        objects[i] = objects[i + 1];
    }

    objectsCount--;

    politObject** newObjects = new politObject * [objectsCount];
    for (int i = 0; i < objectsCount; i++) {
        newObjects[i] = objects[i];
    }
    delete[] objects;
    objects = newObjects;
}

void politObjects::calculationOfAmountOf(const string property, const string continentCondition) {
    if (property == "area") {
        int areaAmount = 0;

        for (int i = 0; i < objectsCount; i++) {
            if (continentCondition == objects[i]->get_continent()) {
                areaAmount += objects[i]->get_area();
            }
        }

        cout << "\n[ ����� ] ��������� ������� ���������� ���������� " << continentCondition << " ����� " << areaAmount << endl;
    }
    else if (property == "population") {
        long long populationAmount = 0;

        for (int i = 0; i < objectsCount; i++) {
            if (continentCondition == objects[i]->get_continent()) {
                populationAmount += objects[i]->get_population();
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

        for (int i = 0; i < objectsCount; i++) {
            if (dynamic_cast<State*>(objects[i]) != nullptr && dynamic_cast<State*>(objects[i])->get_language() == languageCondition) {
                if (objects[i]->get_area() > areaMax) {
                    areaMax = objects[i]->get_area();
                    maxIndex = i;
                }
            }
        }

        if (maxIndex != -1) {
            cout << "\n[ ����� ] ����� ������� ����������� �� ����� " << languageCondition << ": " << endl;
            cout << *dynamic_cast<State*>(objects[maxIndex]);
        }
        else {
            cout << "\n[ ����� ] ��� ���������� �� ����� " << languageCondition << endl;
        }
    }
    else if (property == "population") {
        int maxIndex = -1;
        long long populationMax = 0;

        for (int i = 0; i < objectsCount; i++) { 
            if (dynamic_cast<State*>(objects[i]) != nullptr && dynamic_cast<State*>(objects[i])->get_language() == languageCondition) {
                if (objects[i]->get_population() > populationMax) {
                    populationMax = objects[i]->get_population();
                    maxIndex = i;
                }
            }
        }

        if (maxIndex != -1) {
            cout << "\n[ ����� ] ����� ������� �� ��������� ����������� �� ����� " << languageCondition << ": " << endl;
            cout << *dynamic_cast<State*>(objects[maxIndex]);
        }
        else {
            cout << "\n[ ����� ] ��� ���������� �� ����� " << languageCondition << endl;
        }
    }
    else {
        cerr << "\n\n[ ������ ] ������������ �������� " << property << endl;
    }
}


politObjects::politObjects(const string FILE_PATH) {
    ifstream infile(FILE_PATH);

    if (!infile.is_open()) {
        cerr << "\n\n[ ������ ] ������ �������� �����!" << endl;
        exit(1);
    }

    infile >> statesCount >> citiesCount;

    if (statesCount < 0 || citiesCount < 0) {
        cerr << "\n[ ������ ] ������������ �������� statesCount/citiesCount: " << statesCount << "/" << citiesCount << endl;
        return;
    }

    objectsCount = statesCount + citiesCount;
    objects = new politObject * [objectsCount];

    for (int i = 0; i < statesCount; i++) {
        State* state = new State();
        if (state->initFromFile(infile)) {
            objects[i] = state;
            cout << *state;
        }
        else {
            delete state;
            cerr << "\n[ ������ ] ������ ������ ������� ������ �� �����!" << endl;
            exit(1);
        }
    }

    for (int i = statesCount; i < objectsCount; i++) {
        City* city = new City();
        if (city->initFromFile(infile)) {
            objects[i] = city;
        }
        else {
            delete city;
            cerr << "\n[ ������ ] ������ ������ ������� ����� �� �����!" << endl;
            exit(1);
        }
    }

    infile.close();
}

void politObjects::saveData() {
    ofstream outfile("output.txt");
    if (!outfile.is_open()) {
        cerr << "\n[ ������ ] ������ �������� ����� ��� ������!" << endl;
        return;
    }

    outfile << statesCount << " " << citiesCount << endl;

    for (int i = 0; i < objectsCount; ++i) {
        if (typeid(*objects[i]) == typeid(State)) {
            State* state = dynamic_cast<State*>(objects[i]);
            outfile << *state << endl;
        }
    }

    for (int i = 0; i < objectsCount; ++i) {
        if (typeid(*objects[i]) == typeid(City)) {
            City* city = dynamic_cast<City*>(objects[i]);
            outfile << *city << endl;
        }
    }

    outfile.close();
    cout << "\n[ ������� ] ������ ������� ��������� � ����!" << endl;
}

void politObjects::searchByName() {
    string searchName;
    cout << "[ ������� ] ������� �������� ������� ��� ������: " << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, searchName);

    for (int i = 0; i < objectsCount; ++i) {
        if (objects[i]->get_name() == searchName) {
            cout << "\n======================" << endl;
            cout << "| ������ �" << i + 1 << endl;
            cout << "----------------------" << endl;
            if (typeid(*objects[i]) == typeid(State)) {
                State* state = dynamic_cast<State*>(objects[i]);
                cout << *state;
            }
            else if (typeid(*objects[i]) == typeid(City)) {
                City* city = dynamic_cast<City*>(objects[i]);
                cout << *city;
            }
            cout << "======================" << endl << endl;
            return;
        }
    }

    cout << "[ ������� ] ������ � ����� ��������� �� ������" << endl;
}

politObjects::~politObjects() {
    for (int i = 0; i < objectsCount; ++i) {
        delete objects[i];
    }
    objectsCount = 0;
    delete[] objects;
}

politObjects& politObjects::operator+=(const City& newCity) {
    politObject** newObjects = new politObject * [objectsCount + 1];

    for (int i = 0; i < objectsCount; i++) {
        newObjects[i] = objects[i];
    }

    newObjects[objectsCount] = new City (newCity);

    delete[] objects;
    objects = newObjects;

    objectsCount++;

    return *this;
}

politObjects& politObjects::operator+=(const State& newState) {
    politObject** newObjects = new politObject * [objectsCount + 1];

    for (int i = 0; i < objectsCount; i++) {
        newObjects[i] = objects[i];
    }

    newObjects[objectsCount] = new State (newState);

    delete[] objects;
    objects = newObjects;

    objectsCount++;

    return *this;
}

ostream& operator<<(ostream& os, politObjects& list) {
    int ITERATIONS = list.get_objectsCount();
    for (int i = 0; i < ITERATIONS; ++i) {
        os << "======================" << endl;
        os << "| ������ �" << i + 1 << endl;
        os << "----------------------" << endl;
        if (typeid(*list.objects[i]) == typeid(State)) {
            State* TEMP = dynamic_cast<State*>(list.objects[i]);
            os << *TEMP;
        }
        else if (typeid(*list.objects[i]) == typeid(City)) {
            City* TEMP = dynamic_cast<City*>(list.objects[i]);
            os << *TEMP;
        }
        os << "======================" << endl << endl;
    }

    return os;
}

void newRecord(politObjects& list) {
    string objectType;
    cout << "������� ��� ������� (������ ��� �����): ";
    cin >> objectType;

    if (objectType == "������") {
        State newRecord;
        cin >> newRecord;
        list += newRecord;
    }
    else if (objectType == "�����") {
        City newRecord;
        cin >> newRecord;
        list += newRecord;
    }
    else {
        cout << "�������� ��� �������." << endl;
    }
}

int getUserAction() {
    int action;
    cout << "\n[ ������� ] �������� ��������:\n"
        << "| [ 1 ] ���������� ��������� ������� � ��������� ���������� �������� �������\n"
        << "| [ 2 ] ������� �� ����� �������� � ������� ������ �������� �� ����������� ��������� ������-�������� �����������\n"
        << "| [ 3 ] �������� ����� ������ � ������\n"
        << "| [ 4 ] ������� ������ �� ������\n"
        << "| [ 5 ] ��������� ������ � ����\n"
        << "| [ 6 ] ����� �� ��������\n"
        << "| [ 7 ] ����� �� ���������\n"
        << "[ ������� ] ����: ";
    cin >> action;

    if ((action <= 7) && (action >= 1)) {
        return action;
    }

    return -1;
}


int getObjectsCount(const string FILE_PATH) {
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

string boolToString(bool VALUE) {
    if (VALUE) return "+";
    else return "x";
}

bool stringToBool(string VALUE) {
    if (VALUE == "+") return true;
    else return false;
}