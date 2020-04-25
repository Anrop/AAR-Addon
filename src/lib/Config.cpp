#include "Config.hpp"

#include <fstream>
#include <nlohmann/json.hpp>

std::string Config::getAuthorization() {
    return authorization;
}

std::string Config::getHostname() {
    return hostname;
}

bool Config::parseConfigFile() {
    try {
        std::ifstream ifs("aar.json");
        nlohmann::json config = nlohmann::json::parse(ifs);
        if (config.is_object()) {
            if (!config["hostname"].is_string()) {
                return false;
            }

            hostname = config["hostname"].get<std::string>();

            if (config["authorization"].is_string()) {
                authorization = config["authorization"].get<std::string>();
            }

            return true;
        }

        return false;
    } catch (...) {
        return false;
    }
}
