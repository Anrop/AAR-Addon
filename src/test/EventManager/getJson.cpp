#include <catch2/catch.hpp>
#include <nlohmann/json.hpp>

#include <EventManager.hpp>

using json = nlohmann::json;

TEST_CASE( "EventManager can generate Json", "[EventManager]" ) {

    GIVEN( "An EventManager with one event" ) {
        EventManager em;
        em.addEvent( "{\"test\":\"test\"}" );

        REQUIRE( em.count() == 1 );

        WHEN( "json is generated" ) {
            std::string jsonStr = em.getJson();
            json j = json::parse(jsonStr);

            THEN( "it should contain an events array with one event" ) {
                REQUIRE( j["events"].size() == 1 );
            }

            THEN( "it should contain a valid event" ) {
                json event = j["events"][0];
                REQUIRE( event["test"] == "test" );
                REQUIRE( event["timestamp"].is_string() );
            }
        }
    }
}
