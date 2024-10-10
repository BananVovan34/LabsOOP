#include "lab.h"
#include <stdio.h>
#include <locale.h>
#include <Windows.h>

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    lab();

    return 0;
}