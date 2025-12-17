#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class ContactHandler {
public:
    static const int COUNT = 4;

    static const string names[COUNT];
    static const string links[COUNT];

    string lastOpened;

    // Конструктор по умолчанию
    ContactHandler() : lastOpened("") {}

    // Конструктор копирования
    ContactHandler(const ContactHandler& other) : lastOpened(other.lastOpened) {}

    // Отображение контактов
    void showContacts() const {
        cout << "Доступные контакты:" << endl;
        for (int i = 0; i < COUNT; i++)
            cout << "- " << names[i] << " : " << links[i] << endl;
    }

    // Открытие контакта
    void openContact(const string& name) {
        for (int i = 0; i < COUNT; i++) {
            if (names[i] == name) {
                lastOpened = name;
                cout << "Открываем контакт: " << names[i] << " → " << links[i] << endl;
                return;
            }
        }
        throw runtime_error("Контакт '" + name + "' не найден!");
    }

    const string& getLastOpenedContact() const {
        return lastOpened;
    }

    // Перегрузка оператора [] для доступа к контактам
    pair<string, string> operator[](int index) const {
        if (index < 0 || index >= COUNT)
            throw out_of_range("Индекс контакта выходит за пределы");
        return { names[index], links[index] };
    }

    // Перегрузка оператора += для добавления нового контакта
    ContactHandler& operator+=(const pair<string, string>& newContact) {
        // В реальной реализации здесь нужно было бы расширить массивы,
        // но для демонстрации просто покажем сообщение
        cout << "Добавлен контакт: " << newContact.first << " -> " << newContact.second << endl;
        return *this;
    }
};

// Инициализация контактов
const string ContactHandler::names[COUNT] = {
    "Email", "WhatsApp", "Instagram", "Phone"
};

const string ContactHandler::links[COUNT] = {
    "mailto:chinarcity@example.com",
    "https://wa.me/79998765432",
    "https://instagram.com/cafe_chinar",
    "tel:+79998765432"
};