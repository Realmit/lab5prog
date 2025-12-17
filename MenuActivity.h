#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
#include "Activity.h"
using namespace std;

// Производный класс: реализует абстрактный метод execute().
class MenuActivity : public Activity {
public:
    static const int MENU_SIZE = 6;
    static const string items[MENU_SIZE];

private:
    string dailySpecial;

public:
    // Конструктор с вызовом конструктора базового класса.
    MenuActivity(const string& title = "Меню", const string& special = "")
        : Activity(title), dailySpecial(special) {}

    // Перегрузка виртуального метода с вызовом базового варианта.
    void showTitle() const override {
        Activity::showTitle(); // вызов метода базового класса
        cout << "Тип: Стандартное меню\n";
    }

    void execute() const override {
        cout << "Меню:\n";
        for (int i = 0; i < MENU_SIZE; ++i)
            cout << "- " << items[i] << '\n';
        cout << "Блюдо дня: " << (dailySpecial.empty() ? "не задано" : dailySpecial) << '\n';
    }

    void setDailySpecial(const string& sp) {
        dailySpecial = sp;
    }

    const string& operator[](int index) const {
        if (index < 0 || index >= MENU_SIZE)
            throw out_of_range("Индекс вне диапазона");
        return items[index];
    }

    // Поверхностное клонирование: возвращает указатель на копию объекта.
    virtual unique_ptr<MenuActivity> clone() const {
        return make_unique<MenuActivity>(*this);
    }

    // Запрет конструктора копирования по умолчанию: явно объявлен, но не определён как deleted,
    MenuActivity(const MenuActivity& other) = default;

protected:
    // Защищённый оператор присваивания: можно вызывать из производных классов, но не извне.
    MenuActivity& operator=(const MenuActivity& other) {
        if (this != &other) {
            dailySpecial = other.dailySpecial;
        }
        return *this;
    }

};

const string MenuActivity::items[MENU_SIZE] = {
    "Суп-харчо — 320 руб.",
    "Салат Греческий — 280 руб.",
    "Филе лосося — 650 руб.",
    "Ризотто с грибами — 450 руб.",
    "Кофе латте — 180 руб.",
    "Десерт Тирамису — 290 руб."
};