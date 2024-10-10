#include "states.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_LINE_LENGTH 1024 

int getStatesCount(const char* FILE_PATH) {
    FILE* infile;
    errno_t err = fopen_s(&infile, FILE_PATH, "r");
    if (err != 0 || infile == NULL) {
        fprintf(stderr, "\n[ ������ ] ������ �������� �����!\n");
        return -1;
    }

    int COUNT;
    fscanf_s(infile, "%d", &COUNT);
    fclose(infile);

    return COUNT;
}

int getUserAction() {
    int action;
    printf("\n[ ������� ] �������� ��������:\n"
        "1. ���������� ��������� ������� � ��������� ���������� �������� �������\n"
        "2. ������� �� ����� �������� � ������� ������ �������� �� ����������� ��������� ������-�������� �����������\n"
        "3. �������� ����� ���������\n"
        "4. ����� �� ���������\n"
        "[ ������� ] ����: ");
    scanf_s("%d", &action);

    if ((action <= 4) && (action >= 1)) {
        return action;
    }

    return -1;
}

void newRecord(State** states, int* numStates) {
    State* STATES_STACK = (State*)malloc((*numStates + 1) * sizeof(State));
    if (STATES_STACK == NULL) {
        fprintf(stderr, "\n[ ������ ] �� ������� �������� ������\n");
        return;
    }

    for (int i = 0; i < *numStates; i++) {
        STATES_STACK[i] = (*states)[i];
    }

    printf("[ ������� ] ������� �������� ��� ����� ������:\n");

    printf("| ��������:\n");
    fgets(STATES_STACK[*numStates].name, MAX_NAME_LENGTH, stdin);
    STATES_STACK[*numStates].name[strcspn(STATES_STACK[*numStates].name, "\n")] = 0; // �������� \n

    printf("| �������:\n");
    fgets(STATES_STACK[*numStates].capital, MAX_NAME_LENGTH, stdin);
    STATES_STACK[*numStates].capital[strcspn(STATES_STACK[*numStates].capital, "\n")] = 0;

    printf("| ����� ���������:\n");
    fgets(STATES_STACK[*numStates].government, MAX_STRING_LENGTH, stdin);
    STATES_STACK[*numStates].government[strcspn(STATES_STACK[*numStates].government, "\n")] = 0;

    printf("| ����:\n");
    fgets(STATES_STACK[*numStates].language, MAX_STRING_LENGTH, stdin);
    STATES_STACK[*numStates].language[strcspn(STATES_STACK[*numStates].language, "\n")] = 0;

    printf("| �������:\n");
    fgets(STATES_STACK[*numStates].religion, MAX_STRING_LENGTH, stdin);
    STATES_STACK[*numStates].religion[strcspn(STATES_STACK[*numStates].religion, "\n")] = 0;

    printf("| �������:\n");
    scanf_s("%d", &STATES_STACK[*numStates].area);

    printf("| ���������:\n");
    scanf_s("%lld", &STATES_STACK[*numStates].population);

    printf("| ���������:\n");
    fgets(STATES_STACK[*numStates].continent, MAX_STRING_LENGTH, stdin);
    STATES_STACK[*numStates].continent[strcspn(STATES_STACK[*numStates].continent, "\n")] = 0;

    free(*states);

    *states = STATES_STACK;
    (*numStates)++;
}

void readingFromFile(State* states, int numStates, const char* FILE_PATH) {
    FILE* infile;
    errno_t err = fopen_s(&infile, FILE_PATH, "r");
    if (err != 0 || infile == NULL) {
        fprintf(stderr, "\n[ ������ ] ������ �������� �����!\n");
        return;
    }

    char buffer[MAX_LINE_LENGTH];
    fgets(buffer, MAX_LINE_LENGTH, infile); // ���������� ������ ������

    for (int i = 0; i < numStates; i++) {
        fscanf_s(infile, "%s %s %s %s %s %d %lld %s",
            states[i].name, sizeof(states[i].name),
            states[i].capital, sizeof(states[i].capital),
            states[i].government, sizeof(states[i].government),
            states[i].language, sizeof(states[i].language),
            states[i].religion, sizeof(states[i].religion),
            &states[i].area,
            &states[i].population,
            states[i].continent, sizeof(states[i].continent));
    }

    fclose(infile);
}

void calculationOfAmountOf(State* states, int numStates, const char* property, const char* continentCondition) {
    if (strcmp(property, "area") == 0) {
        int areaAmount = 0;

        for (int i = 0; i < numStates; i++) {
            if (strcmp(continentCondition, states[i].continent) == 0) {
                areaAmount += states[i].area;
            }
        }

        printf("\n[ ����� ] ��������� ������� ���������� ���������� %s ����� %d\n", continentCondition, areaAmount);
    }
    else if (strcmp(property, "population") == 0) {
        long long populationAmount = 0;

        for (int i = 0; i < numStates; i++) {
            if (strcmp(continentCondition, states[i].continent) == 0) {
                populationAmount += states[i].population;
            }
        }

        printf("\n[ ����� ] ��������� ��������� ���������� ���������� %s ����� %lld\n", continentCondition, populationAmount);
    }
    else {
        fprintf(stderr, "\n[ ������ ] ������������ �������� %s\n", property);
    }
}

void findMaxOf(State* states, int numStates, const char* property, const char* languageCondition) {
    if (strcmp(property, "area") == 0) {
        int maxIndex = -1;
        int areaMax = 0;

        for (int i = 0; i < numStates; i++) {
            if ((strcmp(languageCondition, states[i].language) == 0) && (areaMax < states[i].area)) {
                maxIndex = i;
                areaMax = states[i].area;
            }
        }

        if (maxIndex != -1) {
            printf("\n[ ����� ] ����� ������� �� ������� �����������, � �������� %s - ��������������� ���� - %s, �� �������� %s\n",
                languageCondition, states[maxIndex].name, states[maxIndex].capital);
        }
        else {
            printf("\n[ ����� ] �� ������� ���������� � ������ %s\n", languageCondition);
        }
    }
    else if (strcmp(property, "population") == 0) {
        int maxIndex = -1;
        long long populationMax = 0;

        for (int i = 0; i < numStates; i++) {
            if ((strcmp(languageCondition, states[i].language) == 0) && (populationMax < states[i].population)) {
                maxIndex = i;
                populationMax = states[i].population;
            }
        }

        if (maxIndex != -1) {
            printf("\n[ ����� ] ����� ������� �� ����������� ��������� �����������, � �������� %s - ��������������� ���� - %s, �� �������� %s\n",
                languageCondition, states[maxIndex].name, states[maxIndex].capital);
        }
        else {
            printf("\n[ ����� ] �� ������� ���������� � ������ %s\n", languageCondition);
        }
    }
    else {
        fprintf(stderr, "\n[ ������ ] ������������ �������� %s\n", property);
    }
}

void dataOutput(State* states, int numStates) {
    printf("done\n");
    for (int i = 0; i < numStates; ++i) {
        printf("======================\n");
        printf("| ��������� �%d\n", i);
        printf("| ��������: %s\n", states[i].name);
        printf("| �������: %s\n", states[i].capital);
        printf("| ����� ���������: %s\n", states[i].government);
        printf("| ����: %s\n", states[i].language);
        printf("| �������: %s\n", states[i].religion);
        printf("| �������: %d\n", states[i].area);
        printf("| ���������: %lld\n", states[i].population);
        printf("| ���������: %s\n", states[i].continent);
        printf("======================\n\n");
    }
}