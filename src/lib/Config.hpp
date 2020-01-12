#pragma once

#include "json.hpp"

class Config {
public:
    std::string getHostname();
    bool parseConfigFile();
private:
    std::string hostname;
};
