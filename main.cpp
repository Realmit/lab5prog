#include <iostream>
#include <windows.h>
#include "CafeApp.h"
#include "Utils.h"

int main() {
    std::cout << "| Начало работы ЧИНАР |" << std::endl;

    std::cout << "\n=== Демонстрация шаблонной функции calculateAverageRating ===\n";
    {
        double dr[] = { 4.5, 4.8, 5.0, 4.2, 4.7 };
        std::cout << "Среднее (double): " << calculateAverageRating(dr, 5) << "/5.0\n";

        std::vector<int> ir = { 4, 5, 4, 3, 5 };
        std::cout << "Среднее (int): " << calculateAverageRating(ir) << "/5\n";
    }

    CafeApp app;
    app.run();

    std::cout << "| Конец |" << std::endl;
    return 0;
}