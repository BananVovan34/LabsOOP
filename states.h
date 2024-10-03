#pragma once
#ifndef STATES_H 
#define STATES_H
#include <iostream>
#include <string>

using namespace std;

struct State {
    string name;
    string capital;
    string government;
    string language;
    string religion;
    int area;
    long long population;
    string continent;
};

int getStatesCount(string FILE_PATH);
int getUserAction();
void newRecord(State* states, int numStates);
void readingFromFile(State* states, int numStates, string FILE_PATH);
void calculationOfAmountOf(State* states, int numStates, string property, string continentCondition);
void findMaxOf(State* states, int numStates, string property, string languageCondition);
void dataOutput(State* states, int numStates);
#endif