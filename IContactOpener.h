#pragma once
#include <string>

class IContactOpener {
public:
    virtual ~IContactOpener() = default;
    virtual void open(const std::string& link) const = 0;
    virtual std::string getType() const = 0;
};