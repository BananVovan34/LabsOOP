#include "states.h"
#include <fstream>
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <algorithm>

using namespace std;

int getStatesCount(string FILE_PATH) {
    ifstream infile(FILE_PATH);
    if (!infile.is_open()) {
        cerr << "[ Ошибка ] Ошибка открытия файла!" << endl;
        return -1;
    }

    int COUNT;
    infile >> COUNT;
    infile.close();

    return COUNT;
}

int getUserAction() {
    int action;
    cout << "Выберите действие:\n"
        << "1. Рассчитать суммарную площадь и население государств Северной Америки\n"
        << "2. Вывести на экран название и столицу самого крупного по численности населения испано-язычного государства\n"
        << "3. Добавить новую структуру\n"
        << "Ввод: ";
    cin >> action;

    if ((action <= 3) && (action >= 1)) {
        return action;
    }
    
    return -1;
}

void newRecord(State* &states, int &numStates) {
    State* STATES_STACK = new State[numStates + 1];
    for (int i = 0; i < numStates; i++) {
        STATES_STACK[i] = states[i];
    }

    State RECORD_STACK;
    cout << "Введите значения для новой записи:" << endl;
    cout << "Название:" << endl;
    cin.ignore();
    getline(cin, RECORD_STACK.name);
    cout << "Столица:" << endl;
    getline(cin, RECORD_STACK.capital);
    cout << "Форма правления:" << endl;
    getline(cin, RECORD_STACK.government);
    cout << "Язык:" << endl;
    getline(cin, RECORD_STACK.language);
    cout << "Религия:" << endl;
    getline(cin, RECORD_STACK.religion);
    cout << "Площадь:" << endl;
    cin >> RECORD_STACK.area;
    cout << "Население:" << endl;
    cin >> RECORD_STACK.population;
    cin.ignore();
    cout << "Континент:" << endl;
    getline(cin, RECORD_STACK.continent);

    STATES_STACK[numStates] = RECORD_STACK;
    delete[] states;

    states = STATES_STACK;
    numStates++;
}

void readingFromFile(State* states, int numStates, string FILE_PATH) {

    ifstream infile(FILE_PATH);
    if (!infile.is_open()) {
        cerr << "[ Ошибка ] Ошибка открытия файла!" << endl;
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

        cout << "Суммарная площадь государств континента " << continentCondition << " равна " << areaAmount << endl;
    }
    else if (property == "population") {
        long long populationAmount = 0;

        for (int i = 0; i < numStates; i++)
        {
            if (continentCondition == states[i].continent) {
                populationAmount += states[i].population;
            }
        }

        cout << "Суммарное население государств континента " << continentCondition << " равна " << populationAmount << endl;
    }
    else {
        cerr << "[ Ошибка ] Некорректный параметр " << property << endl;
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
            cout << "Самое крупное по площади государство, у которого " << languageCondition
                << " - государственный язык - " << states[maxIndex].name << ", со столицей " << states[maxIndex].capital << endl;
        }
        else {
            cout << "Не найдено государств с языком " << languageCondition << endl;
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
            cout << "Самое крупное по численности населения государство, у которого " << languageCondition
                << " - государственный язык - " << states[maxIndex].name << ", со столицей " << states[maxIndex].capital << endl;
        }
        else {
            cout << "Не найдено государств с языком " << languageCondition << endl;
        }
    }
    else {
        cerr << "[ Ошибка ] Некорректный параметр " << property << endl;
    }
}

void dataOutput(State * states, int numStates) {
    for (int i = 0; i < numStates; ++i) {
        cout << i << endl;
        cout << "======================" << endl;
        cout << "Название: " << states[i].name << endl;
        cout << "Столица: " << states[i].capital << endl;
        cout << "Форма правления: " << states[i].government << endl;
        cout << "Язык: " << states[i].language << endl;
        cout << "Религия: " << states[i].religion << endl;
        cout << "Площадь: " << states[i].area << endl;
        cout << "Население: " << states[i].population << endl;
        cout << "Континент: " << states[i].continent << endl << endl;
    }
}