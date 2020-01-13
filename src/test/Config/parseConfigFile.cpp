#include "../catch.hpp"
#include <Config.hpp>

SCENARIO("Config can parse aar.json", "[Config]") {

    GIVEN("An a config object") {
        Config config;

        REQUIRE(config.getHostname() == "");

        WHEN("and json is read") {
            config.parseConfigFile();

            THEN("it sets hostname") {
                REQUIRE(config.getHostname() == "api.aar.anrop.se");
            }
        }
    }
}
