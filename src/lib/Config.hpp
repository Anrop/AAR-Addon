#pragma once

#include <string>

class Config {
public:
    std::string getAuthorization();
    std::string getHostname();
    bool parseConfigFile();
private:
    std::string authorization;
    std::string hostname;
};
