#pragma once
#include "IContactOpener.h"
#include <iostream>

class WhatsAppOpener : public IContactOpener {
public:
    void open(const std::string& link) const override;
    std::string getType() const override;
};