#include "EmailOpener.h"

void EmailOpener::open(const std::string& link) const {
    std::cout << "[Email] Открываем почтовый клиент: " << link << std::endl;
}

std::string EmailOpener::getType() const {
    return "Email";
}