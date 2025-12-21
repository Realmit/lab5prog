#include "PhoneOpener.h"
#include <iostream>

void PhoneOpener::open(const std::string& link) const {
    std::cout << "[Телефон] Инициируем звонок: " << link << std::endl;
}

std::string PhoneOpener::getType() const {
    return "Phone";
}