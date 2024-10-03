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
				calculationOfAmountOf(states, numStates, "area", "��������_�������");
				calculationOfAmountOf(states, numStates, "population", "��������_�������");
				delete[] states;

				break;

			case 2:
				findMaxOf(states, numStates, "area", "���������");
				findMaxOf(states, numStates, "population", "���������");
				delete[] states;

				break;

			case 3:
				newRecord(states, numStates);
				cout << "chjeck" << endl;
				dataOutput(states, numStates);

				delete[] states;

				break;

			default:
				cerr << "[ ������ ] ������������ �������� action" << endl;
		}

		if (states) {
			delete[] states;
		}

		return 0;
	}
	else {
		cerr << "[ ������ ] ������������ �������� numStates " << numStates << endl;

		return 1;
	}
}