#pragma once
#include <iostream>
#include <string>
#include "Activity.h"

class MenuActivity : public Activity {
public:
    static const int MENU_SIZE = 6;
    static const std::string items[MENU_SIZE];

    std::string dailySpecial;

    MenuActivity() : Activity("Меню"), dailySpecial("") {}

    MenuActivity(const MenuActivity& other)
        : Activity(other.title), dailySpecial(other.dailySpecial) {}

    void setDailySpecial(const std::string& sp) {
        dailySpecial = sp;
        std::cout << "Новое блюдо дня установлено: " << dailySpecial << std::endl;
    }

    void showMenu() const {
        showTitle();
        for (int i = 0; i < MENU_SIZE; i++)
            std::cout << "- " << items[i] << std::endl;
        std::cout << "Блюдо дня: " << dailySpecial << std::endl;
    }

    const std::string& operator[](int index) const {
        if (index >= 0 && index < MENU_SIZE)
            return items[index];
        throw std::string("Индекс выходит за пределы меню");
    }

    MenuActivity operator+(const MenuActivity& other) const {
        MenuActivity result(*this);
        if (!dailySpecial.empty() && !other.dailySpecial.empty())
            result.dailySpecial = dailySpecial + " + " + other.dailySpecial;
        else
            result.dailySpecial = dailySpecial.empty() ? other.dailySpecial : dailySpecial;
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const MenuActivity& menu) {
        os << menu.title << ":\n";
        for (int i = 0; i < menu.MENU_SIZE; i++)
            os << "- " << menu.items[i] << std::endl;
        os << "Блюдо дня: " << menu.dailySpecial;
        return os;
    }
};

const std::string MenuActivity::items[MenuActivity::MENU_SIZE] = {
    "Суп-харчо — 320 руб.",
    "Салат Греческий — 280 руб.",
    "Филе лосося — 650 руб.",
    "Ризотто с грибами — 450 руб.",
    "Кофе латте — 180 руб.",
    "Десерт Тирамису — 290 руб."
};