#pragma once
#include <iostream>
#include <string>
using namespace std;

// Абстрактный базовый класс: демонстрирует использование абстрактного класса.
class Activity {
protected:
    string title;

public:
    Activity(const string& title) : title(title) {}

    virtual ~Activity() = default; // Виртуальный деструктор: обеспечивает вызов деструктора производного класса при delete через базовый указатель.

    virtual void showTitle() const {
        cout << "=== " << title << " ===" << endl;
    }


    // Виртуальный метод для полиморфного вывода.
    virtual ostream& print(ostream& os) const {
        os << "Активность: " << title;
        return os;
    }

    friend ostream& operator<<(ostream& os, const Activity& activity) {
        return activity.print(os);
    }

    // Не-виртуальный метод, вызывающий виртуальные методы — демонстрирует полиморфизм.
    void runSafely() const {
        cout << "[Запуск]\n";
        showTitle();  // виртуальный вызов
        execute();    // виртуальный вызов абстрактного метода
        cout << endl;
    }

    // Чисто виртуальный метод: делает класс абстрактным, обязывает наследников реализовать execute().
    virtual void execute() const = 0;
};