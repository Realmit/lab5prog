#pragma once
#include "IContactOpener.h"

class InstagramOpener : public IContactOpener {
public:
    void open(const std::string& link) const override;
    std::string getType() const override;
};