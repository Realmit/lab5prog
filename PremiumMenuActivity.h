#pragma once
#include <memory>
#include "MenuActivity.h"
using namespace std;

// Второй производный класс: иерархия Activity → MenuActivity → PremiumMenuActivity.
class PremiumMenuActivity : public MenuActivity {
private:
    string chefSignature;

public:
    // Конструктор с вызовом конструктора прямого предка (MenuActivity), который вызывает Activity.
    PremiumMenuActivity(const string& title, const string& chef, const string& special = "")
        : MenuActivity(title, special), chefSignature(chef) {}

    // Перегрузка виртуального метода без вызова базового — полная замена поведения.
    void showTitle() const override {
        cout << "✨=== ПРЕМИУМ-МЕНЮ: " << title << " (от " << chefSignature << ") ===✨\n";
    }

    // Перегрузка с расширением поведения родителя.
    void execute() const override {
        MenuActivity::execute(); // вызов метода непосредственного предка
        cout << "\nПодписано: " << chefSignature << '\n';
    }

    // Глубокое клонирование: корректно копирует все поля, включая уникальные для этого класса.
    unique_ptr<MenuActivity> clone() const override {
        return make_unique<PremiumMenuActivity>(*this);
    }

    // Конструктор копирования: явно делегирует базовому классу и копирует собственные поля.
    PremiumMenuActivity(const PremiumMenuActivity& other)
        : MenuActivity(other), chefSignature(other.chefSignature) {}

    // Перегрузка оператора присваивания объектом базового класса.
    PremiumMenuActivity& operator=(const MenuActivity& base) {
        if (this == &base) return *this;
        MenuActivity::operator=(base); 
        return *this;
    }

    // Запрет присваивания копированием: удалён.
    PremiumMenuActivity& operator=(const PremiumMenuActivity&) = delete;
};