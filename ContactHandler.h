#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
#include <utility>

class ContactHandler {
public:
    static const int COUNT = 4;
    static const std::string names[COUNT];
    static const std::string links[COUNT];

    std::string lastOpened;

    ContactHandler() : lastOpened("") {}

    ContactHandler(const ContactHandler& other) : lastOpened(other.lastOpened) {}

    void showContacts() const {
        std::cout << "Доступные контакты:" << std::endl;
        for (int i = 0; i < COUNT; i++)
            std::cout << "- " << names[i] << " : " << links[i] << std::endl;
    }

    void openContact(const std::string& name) {
        for (int i = 0; i < COUNT; i++) {
            if (names[i] == name) {
                lastOpened = name;
                std::cout << "Открываем контакт: " << names[i] << " → " << links[i] << std::endl;
                return;
            }
        }
        throw std::runtime_error("Контакт '" + name + "' не найден!");
    }

    const std::string& getLastOpenedContact() const {
        return lastOpened;
    }

    std::pair<std::string, std::string> operator[](int index) const {
        if (index < 0 || index >= COUNT)
            throw std::out_of_range("Индекс контакта выходит за пределы");
        return { names[index], links[index] };
    }

    ContactHandler& operator+=(const std::pair<std::string, std::string>& newContact) {
        std::cout << "Добавлен контакт: " << newContact.first << " -> " << newContact.second << std::endl;
        return *this;
    }
};

const std::string ContactHandler::names[COUNT] = {
    "Email", "WhatsApp", "Instagram", "Phone"
};

const std::string ContactHandler::links[COUNT] = {
    "mailto:chinarcity@example.com",
    "https://wa.me/79998765432",
    "https://instagram.com/cafe_chinar",
    "tel:+79998765432"
};