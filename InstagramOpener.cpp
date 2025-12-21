#include "InstagramOpener.h"
#include <iostream>

void InstagramOpener::open(const std::string& link) const {
    std::cout << "[Instagram] Открываем профиль: " << link << std::endl;
}

std::string InstagramOpener::getType() const {
    return "Instagram";
}