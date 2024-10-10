#ifndef STATES_H 
#define STATES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define MAX_STRING_LENGTH 100

typedef struct {
    char name[MAX_NAME_LENGTH];
    char capital[MAX_NAME_LENGTH];
    char government[MAX_STRING_LENGTH];
    char language[MAX_STRING_LENGTH];
    char religion[MAX_STRING_LENGTH];
    int area;
    long long population;
    char continent[MAX_STRING_LENGTH];
} State;

int getStatesCount(const char* FILE_PATH);
int getUserAction();
void newRecord(State** states, int* numStates);
void readingFromFile(State* states, int numStates, const char* FILE_PATH);
void calculationOfAmountOf(State* states, int numStates, const char* property, const char* continentCondition);
void findMaxOf(State* states, int numStates, const char* property, const char* languageCondition);
void dataOutput(State* states, int numStates);

#endif
