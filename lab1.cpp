#include "states.h"

int lab() {
	const string FILE_PATH = "inputStates.txt";

	int numStates = getStatesCount(FILE_PATH);

	if (numStates != -1) {
		State* states = new State[numStates];
		State* newStates = nullptr;

		readingFromFile(states, numStates, FILE_PATH);

		dataOutput(states, numStates);

		bool exit = false;

		while (!(exit)) {
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
				newRecord(states, numStates);
				dataOutput(states, numStates);

				break;

			case 4:
				cout << "[ Система ] Выход из программы...";
				exit = true;

				break;

			default:
				cerr << "\n[ Ошибка ] Некорректный параметр action" << endl << endl;
			}
		}

		if (states) {
			delete[] states;
		}

		return 0;
	}
	else {
		cerr << "\n[ Ошибка ] Некорректный параметр numStates " << numStates << endl;

		return 1;
	}
}