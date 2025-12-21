#include "WhatsAppOpener.h"

void WhatsAppOpener::open(const std::string& link) const {
    std::cout << "[WhatsApp] Открываем чат по ссылке: " << link << std::endl;
    // Реальная интеграция могла бы использовать ShellExecute или системный вызов
}

std::string WhatsAppOpener::getType() const {
    return "WhatsApp";
}