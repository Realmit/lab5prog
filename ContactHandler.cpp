#include "ContactHandler.h"
#include "WhatsAppOpener.h"
#include "EmailOpener.h"
#include "InstagramOpener.h"
#include "PhoneOpener.h"
#include <iostream>
#include <stdexcept>
#include <utility> // для std::move

// Убираем лишние пробелы в ссылках
ContactHandler::ContactHandler() {
    // Динамическая конфигурация по умолчанию (актуальный WhatsApp из KB)
    addContact("Email", "mailto:chinarcity@example.com", createOpener("Email"));
    addContact("WhatsApp", "https://wa.me/79998765432", createOpener("WhatsApp"));      // ← убраны пробелы
    addContact("Instagram", "https://instagram.com/cafe_chinar", createOpener("Instagram")); // ← убраны пробелы
    addContact("Phone", "tel:+79998765432", createOpener("Phone"));
}

void ContactHandler::addContact(const std::string& name, const std::string& link, std::unique_ptr<IContactOpener> opener) {
    // Используем emplace для избежания проблем с ContactEntry
    contacts.emplace(
        name,
        ContactHandler::ContactEntry{ link, std::move(opener) }
    );
}

void ContactHandler::showContacts() const {
    std::cout << "Доступные контакты:" << std::endl;
    for (const auto& kv : contacts) { // используем kv вместо structured binding, если компилятор старый
        std::cout << "- " << kv.first << " → " << kv.second.link << std::endl;
    }
}

void ContactHandler::openContact(const std::string& name) {
    auto it = contacts.find(name);
    if (it == contacts.end()) {
        throw std::runtime_error("Контакт '" + name + "' не найден!");
    }
    lastOpened = name;
    it->second.opener->open(it->second.link);
}

const std::string& ContactHandler::getLastOpenedContact() const {
    return lastOpened;
}

std::unique_ptr<IContactOpener> ContactHandler::createOpener(const std::string& type) {
    if (type == "WhatsApp")   return std::make_unique<WhatsAppOpener>();
    if (type == "Email")      return std::make_unique<EmailOpener>();
    if (type == "Instagram")  return std::make_unique<InstagramOpener>();
    if (type == "Phone")      return std::make_unique<PhoneOpener>();
    return nullptr;
}