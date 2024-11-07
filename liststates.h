#pragma once
#ifndef LISTSTATES_H 
#define LISTSTATES_H

#include <iostream>
#include <string>
#include "states.h"

using namespace std;

class listStates {
private:
    int countStates;
    State* states;
public:
    // Constructor
    listStates(const string FILE_PATH);

    // Getters
    const int get_countStates();

    // Methods
    void calculationOfAmountOf(const string property, const string continentCondition);
    void findMaxOf(const string property, const string languageCondition);

    void deleteRecord();

    // Destructor
    ~listStates();

    // Operators
    listStates& operator+=(const State& newState);
    friend ostream& operator<<(ostream& os, listStates& list);
};

// Another Functions
void newRecord(listStates& list);

#endif