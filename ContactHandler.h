#pragma once
#include <map>
#include <string>
#include <memory>
#include "IContactOpener.h"

class ContactHandler {
private:
    struct ContactEntry {
        std::string link;
        std::unique_ptr<IContactOpener> opener;
    };
    std::map<std::string, ContactEntry> contacts;
    std::string lastOpened;

public:
    ContactHandler();
    void addContact(const std::string& name, const std::string& link, std::unique_ptr<IContactOpener> opener);
    void showContacts() const;
    void openContact(const std::string& name);
    const std::string& getLastOpenedContact() const;

    static std::unique_ptr<IContactOpener> createOpener(const std::string& type);
};