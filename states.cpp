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
        fprintf(stderr, "\n[ Ошибка ] Ошибка открытия файла!\n");
        return -1;
    }

    int COUNT;
    fscanf_s(infile, "%d", &COUNT);
    fclose(infile);

    return COUNT;
}

int getUserAction() {
    int action;
    printf("\n[ Система ] Выберите действие:\n"
        "1. Рассчитать суммарную площадь и население государств Северной Америки\n"
        "2. Вывести на экран название и столицу самого крупного по численности населения испано-язычного государства\n"
        "3. Добавить новую структуру\n"
        "4. Выйти из программы\n"
        "[ Система ] Ввод: ");
    scanf_s("%d", &action);

    if ((action <= 4) && (action >= 1)) {
        return action;
    }

    return -1;
}

void newRecord(State** states, int* numStates) {
    State* STATES_STACK = (State*)malloc((*numStates + 1) * sizeof(State));
    if (STATES_STACK == NULL) {
        fprintf(stderr, "\n[ Ошибка ] Не удалось выделить память\n");
        return;
    }

    for (int i = 0; i < *numStates; i++) {
        STATES_STACK[i] = (*states)[i];
    }

    printf("[ Система ] Введите значения для новой записи:\n");

    printf("| Название:\n");
    fgets(STATES_STACK[*numStates].name, MAX_NAME_LENGTH, stdin);
    STATES_STACK[*numStates].name[strcspn(STATES_STACK[*numStates].name, "\n")] = 0; // Удаление \n

    printf("| Столица:\n");
    fgets(STATES_STACK[*numStates].capital, MAX_NAME_LENGTH, stdin);
    STATES_STACK[*numStates].capital[strcspn(STATES_STACK[*numStates].capital, "\n")] = 0;

    printf("| Форма правления:\n");
    fgets(STATES_STACK[*numStates].government, MAX_STRING_LENGTH, stdin);
    STATES_STACK[*numStates].government[strcspn(STATES_STACK[*numStates].government, "\n")] = 0;

    printf("| Язык:\n");
    fgets(STATES_STACK[*numStates].language, MAX_STRING_LENGTH, stdin);
    STATES_STACK[*numStates].language[strcspn(STATES_STACK[*numStates].language, "\n")] = 0;

    printf("| Религия:\n");
    fgets(STATES_STACK[*numStates].religion, MAX_STRING_LENGTH, stdin);
    STATES_STACK[*numStates].religion[strcspn(STATES_STACK[*numStates].religion, "\n")] = 0;

    printf("| Площадь:\n");
    scanf_s("%d", &STATES_STACK[*numStates].area);

    printf("| Население:\n");
    scanf_s("%lld", &STATES_STACK[*numStates].population);

    printf("| Континент:\n");
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
        fprintf(stderr, "\n[ Ошибка ] Ошибка открытия файла!\n");
        return;
    }

    char buffer[MAX_LINE_LENGTH];
    fgets(buffer, MAX_LINE_LENGTH, infile); // Пропускаем первую строку

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

        printf("\n[ Вывод ] Суммарная площадь государств континента %s равна %d\n", continentCondition, areaAmount);
    }
    else if (strcmp(property, "population") == 0) {
        long long populationAmount = 0;

        for (int i = 0; i < numStates; i++) {
            if (strcmp(continentCondition, states[i].continent) == 0) {
                populationAmount += states[i].population;
            }
        }

        printf("\n[ Вывод ] Суммарное население государств континента %s равна %lld\n", continentCondition, populationAmount);
    }
    else {
        fprintf(stderr, "\n[ Ошибка ] Некорректный параметр %s\n", property);
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
            printf("\n[ Вывод ] Самое крупное по площади государство, у которого %s - государственный язык - %s, со столицей %s\n",
                languageCondition, states[maxIndex].name, states[maxIndex].capital);
        }
        else {
            printf("\n[ Вывод ] Не найдено государств с языком %s\n", languageCondition);
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
            printf("\n[ Вывод ] Самое крупное по численности населения государство, у которого %s - государственный язык - %s, со столицей %s\n",
                languageCondition, states[maxIndex].name, states[maxIndex].capital);
        }
        else {
            printf("\n[ Вывод ] Не найдено государств с языком %s\n", languageCondition);
        }
    }
    else {
        fprintf(stderr, "\n[ Ошибка ] Некорректный параметр %s\n", property);
    }
}

void dataOutput(State* states, int numStates) {
    printf("done\n");
    for (int i = 0; i < numStates; ++i) {
        printf("======================\n");
        printf("| Структура №%d\n", i);
        printf("| Название: %s\n", states[i].name);
        printf("| Столица: %s\n", states[i].capital);
        printf("| Форма правления: %s\n", states[i].government);
        printf("| Язык: %s\n", states[i].language);
        printf("| Религия: %s\n", states[i].religion);
        printf("| Площадь: %d\n", states[i].area);
        printf("| Население: %lld\n", states[i].population);
        printf("| Континент: %s\n", states[i].continent);
        printf("======================\n\n");
    }
}