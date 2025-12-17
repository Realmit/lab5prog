#pragma once
#include <iostream>
#include <string>
#include "Activity.h"
using namespace std;

class MenuActivity : public Activity {
public:
    static const int MENU_SIZE = 6;
    static const string items[MENU_SIZE];

    string dailySpecial;

    // Конструктор по умолчанию
    MenuActivity() : Activity("Меню"), dailySpecial("") {}

    // Конструктор копирования
    MenuActivity(const MenuActivity& other)
        : Activity(other.title),
        dailySpecial(other.dailySpecial) {}

    // Установка блюда дня
    void setDailySpecial(const string& sp) {
        this->dailySpecial = sp;
        cout << "Новое блюдо дня установлено: " << this->dailySpecial << endl;
    }

    // Отображение меню
    void showMenu() const {
        showTitle();
        for (int i = 0; i < MENU_SIZE; i++)
            cout << "- " << items[i] << endl;
        cout << "Блюдо дня: " << dailySpecial << endl;
    }

    // Перегрузка оператора [] для доступа к элементам меню
    const string& operator[](int index) const {
        if (index >= 0 && index < MENU_SIZE)
            return items[index];
        throw string("Индекс выходит за пределы меню");
    }

    // Перегрузка оператора + для объединения меню
    MenuActivity operator+(const MenuActivity& other) const {
        MenuActivity result(*this);
        result.dailySpecial += " + " + other.dailySpecial;
        return result;
    }
    // Перегрузка оператора вывода
    friend ostream& operator<<(ostream& os, const MenuActivity& menu) {
        os << menu.title << ":\n";
        for (int i = 0; i < menu.MENU_SIZE; i++)
            os << "- " << menu.items[i] << endl;
        os << "Блюдо дня: " << menu.dailySpecial;
        return os;
    }
};

// Инициализация статического массива меню
const string MenuActivity::items[MenuActivity::MENU_SIZE] = {
    "Суп-харчо — 320 руб.",
    "Салат Греческий — 280 руб.",
    "Филе лосося — 650 руб.",
    "Ризотто с грибами — 450 руб.",
    "Кофе латте — 180 руб.",
    "Десерт Тирамису — 290 руб."
};