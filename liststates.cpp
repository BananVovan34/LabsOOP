#include <fstream>
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <algorithm>

#include "states.h"
#include "liststates.h"

//
// Getters
//

const int listStates::get_countStates() { return countStates; };

//
// listStates Methods
//

void listStates::deleteRecord() {
    int INDEX;

    if (countStates <= 0) {
        cerr << "\n[ Ошибка ] В списке объектов всего лишь 1 объект, вы его не можете удалить" << endl;
        return;
    }

    while (true) {
        cout << "\n[ Система ] Введите порядковый номер удаляемого объекта: " << endl;
        cin >> INDEX;
        INDEX--;

        if (INDEX < 0 || INDEX >= countStates) {
            cerr << "\n[ Ошибка ] Неверный индекс для удаления! Выберите индекс в пределах от 1 до " << countStates << endl;
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

        cout << "\n[ Вывод ] Суммарная площадь государств континента " << continentCondition << " равна " << areaAmount << endl;
    }
    else if (property == "population") {
        long long populationAmount = 0;

        for (int i = 0; i < countStates; i++)
        {
            if (continentCondition == states[i].get_continent()) {
                populationAmount += states[i].get_population();
            }
        }

        cout << "\n[ Вывод ] Суммарное население государств континента " << continentCondition << " равна " << populationAmount << endl;
    }
    else {
        cerr << "\n\n[ Ошибка ] Некорректный параметр " << property << endl;
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
            cout << "\n[ Вывод ] Самое крупное по площади государство, у которого " << languageCondition
                << " - государственный язык - " << states[maxIndex].get_name() << ", со столицей " << states[maxIndex].get_capital() << endl;
        }
        else {
            cout << "\n[ Вывод ] Не найдено государств с языком " << languageCondition << endl;
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
            cout << "\n[ Вывод ] Самое крупное по численности населения государство, у которого " << languageCondition
                << " - государственный язык - " << states[maxIndex].get_name() << ", со столицей " << states[maxIndex].get_capital() << endl;
        }
        else {
            cout << "\n[ Вывод ] Не найдено государств с языком " << languageCondition << endl;
        }
    }
    else {
        cerr << "\n\n[ Ошибка ] Некорректный параметр " << property << endl;
    }
}

listStates::listStates(const string FILE_PATH) {
    countStates = getStatesCount(FILE_PATH);

    if (countStates != -1) {
        states = new State[countStates];

        ifstream infile(FILE_PATH);
        if (!infile.is_open()) {
            cerr << "\n\n[ Ошибка ] Ошибка открытия файла!" << endl;
            return;
        }

        infile.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int i = 0; i < countStates; i++) {
            states[i].initFromFile(infile);
        }

        infile.close();
    }
    else {
        cerr << "\n[ Ошибка ] Некорректный параметр numStates " << countStates << endl;
    }
}

listStates::~listStates() {
    delete[] states;
}

//
// Operators
// 

listStates& listStates::operator+=(const State& newState) {
    State* newStatesArray = new State[countStates + 1];
    for (int i = 0; i < countStates; ++i) {
        newStatesArray[i] = states[i];
    }
    newStatesArray[countStates] = newState;
    delete[] states;
    states = newStatesArray;
    ++countStates;
    return *this;
}

ostream& operator<<(ostream& os, listStates& list) {
    int ITERATIONS = list.get_countStates();
    for (int i = 0; i < ITERATIONS; ++i) {
        os << "======================" << endl;
        os << "| Структура №" << i + 1 << endl;
        os << list.states[i];
        os << "======================" << endl << endl;
    }

    return os;
}

//
// Another Functions
//

void newRecord(listStates& list) {
    State NEW_RECORD;
    cin >> NEW_RECORD;

    list += NEW_RECORD;
}