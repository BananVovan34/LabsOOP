#pragma once
#ifndef POLITOBJECTS_H 
#define POLITOBJECTS_H

#include <iostream>
#include <string>

using namespace std;

class politObject {
protected:
    string name;
    int area;
    long long population;
    string continent;
public:
    virtual bool initFromFile(ifstream& infile);

    const string get_name();
    const int get_area();
    const long long get_population();
    const string get_continent();
};

class State : public politObject {
private:
    string capital;
    string government;
    string language;
    string religion;
public:
    const string get_capital();
    const string get_government();
    const string get_language();
    const string get_religion();

    void set_name(string VALUE);
    void set_capital(string VALUE);
    void set_government(string VALUE);
    void set_language(string VALUE);
    void set_religion(string VALUE);
    void set_area(int VALUE);
    void set_population(long long VALUE);
    void set_continent(string VALUE);

    State();
    State(string set_name, string set_capital, string set_government, string set_language, string set_religion, int set_area, long long set_population, string set_continent);
    State(const State& STACK);

    bool initFromFile(ifstream& infile);

    bool operator==(const State& other) const;
    bool operator!=(const State& other) const;
    friend ostream& operator<<(ostream& os, State& state);
    friend istream& operator>>(istream& is, State& state);
};

class City : public politObject {
private:
    string state;
    string mayor;
    long long budget;
    bool isCapital;
public:
    bool initFromFile(ifstream& infile);

    City();
    City(string set_name, bool set_isCapital, string set_state, string set_mayor, long long set_budget, int set_area, long long set_population, string set_continent);

    const string get_state();
    const string get_mayor();
    const long long get_budget();
    const bool get_isCapital();

    friend ostream& operator<<(ostream& os, State& state);
    friend istream& operator>>(istream& is, State& state);
};

class politObjects {
private:
    int objectsCount;
    int statesCount;
    int citiesCount;
    politObject ** objects;
public:
    politObjects(const string FILE_PATH);

    const int get_objectsCount();

    void calculationOfAmountOf(const string property, const string continentCondition);
    void findMaxOf(const string property, const string languageCondition);

    void deleteRecord();
    void saveData();
    void searchByName();

    ~politObjects();

    politObjects& operator+=(const State& newState);
    politObjects& operator+=(const City& newCity);
    friend ostream& operator<<(ostream& os, politObjects& list);
};

void newRecord(politObjects& list);
int getObjectsCount(const string FILE_PATH);
int getUserAction();
string boolToString(bool VALUE);
bool stringToBool(string VALUE);
#endif