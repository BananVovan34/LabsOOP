#include <locale.h>
#include <Windows.h>
#include <iostream>

#include "lab.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    try {
        lab();

        return 0;
    }
    catch (void * error_message) {
        cerr << "\n[ Ошибка ] " << error_message << endl;

        return -1;
    }
}