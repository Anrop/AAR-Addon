#include "Config.hpp"
#include <boost/date_time.hpp>

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

            hostname = config["hostname"];

            if (config["authorization"].is_string()) {
                authorization = config["authorization"];
            }

            return true;
        }

        return false;
    } catch (...) {
        return false;
    }
}
