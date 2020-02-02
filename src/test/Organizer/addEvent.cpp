#include <catch2/catch.hpp>

#include <Organizer.hpp>

TEST_CASE( "Organizer can add events", "[Organizer]" ) {

    GIVEN( "An Organizer" ) {
        Organizer organizer;

        WHEN( "an event is added" ) {
            EventManager::event_added result = organizer.addEvent("{\"type\":\"empty\"}");

            THEN ( "event is successfully added" ) {
                REQUIRE( result == EventManager::EVENT_OK );
            }

            THEN( "events are processed" ) {
                organizer.waitForEventsToProcess();
                REQUIRE( organizer.getEventsCount() == 0);
            }
        }

        WHEN( "an invalid event is added" ) {
            EventManager::event_added result = organizer.addEvent("{\"type\":\"empty");

            THEN ( "event is rejected due to invalid format" ) {
                REQUIRE( result == EventManager::EVENT_PARSE_ERROR );
            }
        }
    }
}
