#include <iostream>
#include <windows.h>
#include "CafeApp.h"
using namespace std;

int main() {
    // Настройка кодировки для Windows

    cout << "| Начало работы ЧИНАР |" << endl;

    // Создание и запуск приложения
    CafeApp app;
    app.run();

    cout << "| Конец |" << endl;
    return 0;
}