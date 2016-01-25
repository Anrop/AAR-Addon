#include "../catch.hpp"
#include <EventManager.hpp>

SCENARIO( "EventManager can generate Json", "[EventManager]" ) {

    GIVEN( "An EventManager with one event" ) {
        EventManager *em = new EventManager;
        em->addEvent( "test=test" );

        REQUIRE( em->count() == 1 );
        REQUIRE( !em->isEmpty() );

        WHEN( "and json is generated" ) {
            std::string json = em->getJson();

            THEN( "it should generate non-empty json" ) {
                REQUIRE( json.length() > 0 );
            }
        }
    }
}
