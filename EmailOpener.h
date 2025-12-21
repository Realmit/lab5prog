#pragma once
#include "IContactOpener.h"
#include <iostream>

class EmailOpener : public IContactOpener {
public:
    void open(const std::string& link) const override;
    std::string getType() const override;
};