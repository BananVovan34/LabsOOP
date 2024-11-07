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
    virtual bool initFromFile(ifstream& infile) = 0;
    virtual const string get_name() = 0;
    virtual const string get_capital() = 0;
    virtual const string get_government() = 0;
    virtual const string get_language() = 0;
    virtual const string get_religion() = 0;
    virtual const int get_area() = 0;
    virtual const long long get_population() = 0;
    virtual const string get_continent() = 0;
};

class State : public politObject {
private:
    string capital;
    string government;
    string language;
    string religion;
public:
    // Getters
    const string get_name() override;
    const string get_capital() override;
    const string get_government() override;
    const string get_language() override;
    const string get_religion() override;
    const int get_area() override;
    const long long get_population() override;
    const string get_continent() override;

    // Setters
    void set_name(string VALUE);
    void set_capital(string VALUE);
    void set_government(string VALUE);
    void set_language(string VALUE);
    void set_religion(string VALUE);
    void set_area(int VALUE);
    void set_population(long long VALUE);
    void set_continent(string VALUE);

    // Constructors
    State();
    State(string set_name, string set_capital, string set_government, string set_language, string set_religion, int set_area, long long set_population, string set_continent);
    State(const State& STACK);

    // Methods
    bool initFromFile(ifstream& infile) override;

    // Operators
    bool operator==(const State& other) const;
    bool operator!=(const State& other) const;
    friend ostream& operator<<(ostream& os, State& state);
    friend istream& operator>>(istream& is, State& state);
};

class City : public politObject {
private:
    string mayor;
    double budget;
    bool isCapital;
public:

    bool initFromFile(ifstream& infile) override;
};

class politObjects {
private:
    int objectsCount;
    politObject* objects;
public:
    // Constructor
    politObjects(const string FILE_PATH);

    // Getters
    const int get_objectsCount();

    // Methods
    void calculationOfAmountOf(const string property, const string continentCondition);
    void findMaxOf(const string property, const string languageCondition);

    void deleteRecord();

    // Destructor
    ~politObjects();

    // Operators
    politObjects& operator+=(const State& newState);
    friend ostream& operator<<(ostream& os, politObjects& list);
};

// Another Functions
void newRecord(politObjects& list);
int getStatesCount(const string FILE_PATH);
int getUserAction();
#endif