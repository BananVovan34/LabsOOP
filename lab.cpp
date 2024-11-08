#include "politobjects.h"

int lab() {
	const string FILE_PATH = "inputStates.txt";

	if (getObjectsCount(FILE_PATH) != -1) {
		politObjects listOfObjects(FILE_PATH);

		cout << listOfObjects;

		bool exit = false;

		while (!(exit)) {
			switch (getUserAction()) {
			case 1:
				listOfObjects.calculationOfAmountOf("area", "Северная_Америка");
				listOfObjects.calculationOfAmountOf("population", "Северная_Америка");

				break;

			case 2:
				listOfObjects.findMaxOf("area", "Испанский");
				listOfObjects.findMaxOf("population", "Испанский");

				break;

			case 3:
				newRecord(listOfObjects);
				cout << listOfObjects;

				break;

			case 4:
				listOfObjects.deleteRecord();
				cout << listOfObjects;

				break;

			case 5:
				listOfObjects.saveData();

				break;

			case 6:
				listOfObjects.searchByName();

				break;

			case 7:
				cout << "\n[ Система ] Выход из программы...";
				exit = true;

				break;

			default:
				cerr << "\n[ Ошибка ] Некорректный параметр action" << endl << endl;
			}
		}

		listOfObjects.~politObjects();

		return 0;
	}
	else {
		cerr << "\n[ Ошибка ] Некорректный параметр количества объектов" << endl;

		return 1;
	}
}