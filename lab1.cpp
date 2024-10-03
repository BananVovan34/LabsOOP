#include "states.h"

int lab1() {
	const string FILE_PATH = "inputStates.txt";

	int numStates = getStatesCount(FILE_PATH);

	if (numStates != -1) {
		State* states = new State[numStates];
		State* newStates = nullptr;

		readingFromFile(states, numStates, FILE_PATH);

		dataOutput(states, numStates);

		int action = getUserAction();

		switch (action) {
			case 1:
				calculationOfAmountOf(states, numStates, "area", "Северная_Америка");
				calculationOfAmountOf(states, numStates, "population", "Северная_Америка");
				delete[] states;

				break;

			case 2:
				findMaxOf(states, numStates, "area", "Испанский");
				findMaxOf(states, numStates, "population", "Испанский");
				delete[] states;

				break;

			case 3:
				numStates += 1;

				newStates = new State[numStates];
				for (int i = 0; i < (numStates - 1); i++) {
					newStates[i] = states[i];
				}
				dataOutput(newStates, numStates-1);

				delete[] states;

				newRecord(newStates, numStates);
				dataOutput(newStates, numStates);

				delete[] newStates;

				break;

			default:
				cerr << "[ Ошибка ] Некорректный параметр action" << endl;
		}

		if (states) {
			delete[] states;
		}

		return 0;
	}
	else {
		cerr << "[ Ошибка ] Некорректный параметр numStates " << numStates << endl;

		return 1;
	}
}