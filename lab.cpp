#include "states.h"

int lab() {
	const string FILE_PATH = "inputStates.txt";

	int n = getStatesCount(FILE_PATH);

	if (n != -1) {
		listStates states(FILE_PATH);

		states.dataOutput();

		bool exit = false;

		while (!(exit)) {
			int action = getUserAction();

			switch (action) {
			case 1:
				states.calculationOfAmountOf("area", "Северная_Америка");
				states.calculationOfAmountOf("population", "Северная_Америка");

				break;

			case 2:
				states.findMaxOf("area", "Испанский");
				states.findMaxOf("population", "Испанский");

				break;

			case 3:
				states.newRecord();
				states.dataOutput();

				break;

			case 4:
				states.deleteRecord();
				states.dataOutput();

				break;

			case 5:
				cout << "\n[ Система ] Выход из программы...";
				exit = true;

				break;

			default:
				cerr << "\n[ Ошибка ] Некорректный параметр action" << endl << endl;
			}
		}

		states.~listStates();

		return 0;
	}
	else {
		cerr << "\n[ Ошибка ] Некорректный параметр количества объектов: " << n << endl;

		return 1;
	}
}