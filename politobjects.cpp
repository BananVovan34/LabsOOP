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
    os << "| Название: " << state.get_name() << endl;
    os << "| Столица: " << state.get_capital() << endl;
    os << "| Форма правления: " << state.get_government() << endl;
    os << "| Язык: " << state.get_language() << endl;
    os << "| Религия: " << state.get_religion() << endl;
    os << "| Площадь: " << state.get_area() << endl;
    os << "| Население: " << state.get_population() << endl;
    os << "| Континент: " << state.get_continent() << endl;
    return os;
}

istream& operator>>(istream& is, State& state) {
    string name, capital, government, language, religion, continent;
    int area;
    long long population;

    cout << "\n[ Система ] Введите значения для нового объекта:" << endl;
    cout << "| Название:" << endl;
    is.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(is, name);
    cout << "| Столица:" << endl;
    getline(is, capital);
    cout << "| Форма правления:" << endl;
    getline(is, government);
    cout << "| Язык:" << endl;
    getline(is, language);
    cout << "| Религия:" << endl;
    getline(is, religion);
    cout << "| Площадь:" << endl;
    is >> area;
    cout << "| Население:" << endl;
    is >> population;
    is.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "| Континент:" << endl;
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
        cerr << "\n\n[ Ошибка ] Ошибка открытия файла!" << endl;
        return -1;
    }

    int COUNT;
    infile >> COUNT;
    infile.close();

    return COUNT;
}

int getUserAction() {
    int action;
    cout << "\n[ Система ] Выберите действие:\n"
        << "| [ 1 ] Рассчитать суммарную площадь и население государств Северной Америки\n"
        << "| [ 2 ] Вывести на экран название и столицу самого крупного по численности населения испано-язычного государства\n"
        << "| [ 3 ] Добавить новый объект в список\n"
        << "| [ 4 ] Удалить объект из списка\n"
        << "| [ 5 ] Выйти из программы\n"
        << "[ Система ] Ввод: ";
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
        cerr << "\n[ Ошибка ] В списке объектов всего лишь 1 объект, вы его не можете удалить" << endl;
        return;
    }

    while (true) {
        cout << "\n[ Система ] Введите порядковый номер удаляемого объекта: " << endl;
        cin >> INDEX;
        INDEX--;

        if (INDEX < 0 || INDEX >= objectsCount) {
            cerr << "\n[ Ошибка ] Неверный индекс для удаления! Выберите индекс в пределах от 1 до " << objectsCount << endl;
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

        cout << "\n[ Вывод ] Суммарная площадь государств континента " << continentCondition << " равна " << areaAmount << endl;
    }
    else if (property == "population") {
        long long populationAmount = 0;

        for (int i = 0; i < objectsCount; i++)
        {
            if (continentCondition == objects[i].get_continent()) {
                populationAmount += objects[i].get_population();
            }
        }

        cout << "\n[ Вывод ] Суммарное население государств континента " << continentCondition << " равна " << populationAmount << endl;
    }
    else {
        cerr << "\n\n[ Ошибка ] Некорректный параметр " << property << endl;
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
            cout << "\n[ Вывод ] Самое крупное по площади государство, у которого " << languageCondition
                << " - государственный язык - " << objects[maxIndex].get_name() << ", со столицей " << objects[maxIndex].get_capital() << endl;
        }
        else {
            cout << "\n[ Вывод ] Не найдено государств с языком " << languageCondition << endl;
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
            cout << "\n[ Вывод ] Самое крупное по численности населения государство, у которого " << languageCondition
                << " - государственный язык - " << objects[maxIndex].get_name() << ", со столицей " << objects[maxIndex].get_capital() << endl;
        }
        else {
            cout << "\n[ Вывод ] Не найдено государств с языком " << languageCondition << endl;
        }
    }
    else {
        cerr << "\n\n[ Ошибка ] Некорректный параметр " << property << endl;
    }
}

politObjects::politObjects(const string FILE_PATH) {
    objectsCount = getStatesCount(FILE_PATH);

    if (objectsCount != -1) {
        objects = new State[objectsCount];

        ifstream infile(FILE_PATH);
        if (!infile.is_open()) {
            cerr << "\n\n[ Ошибка ] Ошибка открытия файла!" << endl;
            return;
        }

        infile.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int i = 0; i < objectsCount; i++) {
            objects[i].initFromFile(infile);
        }

        infile.close();
    }
    else {
        cerr << "\n[ Ошибка ] Некорректный параметр numStates " << objectsCount << endl;
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
        os << "| Структура №" << i + 1 << endl;
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