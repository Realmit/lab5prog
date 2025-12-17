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

    ContactHandler() = default;

    ContactHandler(const ContactHandler& other) : lastOpened(other.lastOpened) {}

    void showContacts() const {
        cout << "Доступные контакты:\n";
        for (int i = 0; i < COUNT; ++i)
            cout << "- " << names[i] << " : " << links[i] << '\n';
    }

    void openContact(const string& name) {
        for (int i = 0; i < COUNT; ++i) {
            if (names[i] == name) {
                lastOpened = name;
                cout << "Открываем контакт: " << names[i] << " → " << links[i] << '\n';
                return;
            }
        }
        throw runtime_error("Контакт '" + name + "' не найден!");
    }

    const string& getLastOpenedContact() const {
        return lastOpened.empty() ? string("не выбран") : lastOpened;
    }
};

const string ContactHandler::names[COUNT] = {
    "Email", "WhatsApp", "Instagram", "Phone"
};

const string ContactHandler::links[COUNT] = {
    "mailto:chinarcity@example.com",
    "https://wa.me/79998765432",     
    "https://instagram.com/cafe_chinar",
    "tel:+79998765432"
};