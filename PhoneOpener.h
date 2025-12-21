#pragma once
#include "IContactOpener.h"

class PhoneOpener : public IContactOpener {
public:
    void open(const std::string& link) const override;
    std::string getType() const override;
};