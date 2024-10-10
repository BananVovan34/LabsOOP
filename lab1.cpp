#include "states.h"

int lab() {
    const char* FILE_PATH = "inputStates.txt";

    int numStates = getStatesCount(FILE_PATH);

    if (numStates != -1) {
        State* states = (State*)malloc(numStates * sizeof(State));
        if (states == NULL) {
            fprintf(stderr, "\n[ ������ ] �� ������� �������� ������\n");
            return 1;
        }

        readingFromFile(states, numStates, FILE_PATH);

        dataOutput(states, numStates);

        int exit = 0;

        while (!exit) {
            int action = getUserAction();

            switch (action) {
            case 1:
                calculationOfAmountOf(states, numStates, "area", "��������_�������");
                calculationOfAmountOf(states, numStates, "population", "��������_�������");
                break;

            case 2:
                findMaxOf(states, numStates, "area", "���������");
                findMaxOf(states, numStates, "population", "���������");
                break;

            case 3:
                newRecord(&states, &numStates);
                dataOutput(states, numStates);
                break;

            case 4:
                printf("[ ������� ] ����� �� ���������...\n");
                exit = 1;
                break;

            default:
                fprintf(stderr, "\n[ ������ ] ������������ �������� action\n\n");
            }
        }

        if (states) {
            free(states);
        }

        return 0;
    }
    else {
        fprintf(stderr, "\n[ ������ ] ������������ �������� numStates %d\n", numStates);
        return 1;
    }
}
