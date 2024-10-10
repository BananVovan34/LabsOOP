#include "states.h"

int lab() {
    const char* FILE_PATH = "inputStates.txt";

    int numStates = getStatesCount(FILE_PATH);

    if (numStates != -1) {
        State* states = (State*)malloc(numStates * sizeof(State));
        if (states == NULL) {
            fprintf(stderr, "\n[ Ошибка ] Не удалось выделить память\n");
            return 1;
        }

        readingFromFile(states, numStates, FILE_PATH);

        dataOutput(states, numStates);

        int exit = 0;

        while (!exit) {
            int action = getUserAction();

            switch (action) {
            case 1:
                calculationOfAmountOf(states, numStates, "area", "Северная_Америка");
                calculationOfAmountOf(states, numStates, "population", "Северная_Америка");
                break;

            case 2:
                findMaxOf(states, numStates, "area", "Испанский");
                findMaxOf(states, numStates, "population", "Испанский");
                break;

            case 3:
                newRecord(&states, &numStates);
                dataOutput(states, numStates);
                break;

            case 4:
                printf("[ Система ] Выход из программы...\n");
                exit = 1;
                break;

            default:
                fprintf(stderr, "\n[ Ошибка ] Некорректный параметр action\n\n");
            }
        }

        if (states) {
            free(states);
        }

        return 0;
    }
    else {
        fprintf(stderr, "\n[ Ошибка ] Некорректный параметр numStates %d\n", numStates);
        return 1;
    }
}
