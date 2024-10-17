#pragma once
#ifndef STATES_H 
#define STATES_H
#include <iostream>
#include <string>

using namespace std;

class State {
private:
    string name;
    string capital;
    string government;
    string language;
    string religion;
    int area;
    long long population;
    string continent;
public:
    // Getters
    string get_name();
    string get_capital();
    string get_government();
    string get_language();
    string get_religion();
    int get_area();
    long long get_population();
    string get_continent();

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
    bool initFromFile(ifstream& infile);
    void print();
};

class listStates {
private:
    int countStates;
    State* states;
public:
    // Constructor
    listStates(const string FILE_PATH);

    // Methods
    void dataOutput();
    void calculationOfAmountOf(const string property, const string continentCondition);
    void findMaxOf(const string property, const string languageCondition);
    void newRecord();
    void deleteRecord();

    // Destructor
    ~listStates();
};

// Another Functions
int getStatesCount(const string FILE_PATH);
int getUserAction();
#endif