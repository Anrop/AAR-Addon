#include "../catch.hpp"
#include <EventManager.hpp>

SCENARIO( "EventManager can clear events", "[EventManager]" ) {

    GIVEN( "An EventManager with one event" ) {
        EventManager *em = new EventManager;
        em->addEvent( "test=test" );

        REQUIRE( em->count() == 1 );
        REQUIRE( !em->isEmpty() );

        WHEN( "and events are cleared" ) {
            em->clearEvents();

            THEN( "it contains zero item and is empty" ) {
                REQUIRE( em->count() == 0 );
                REQUIRE( em->isEmpty() );
            }
        }
    }
}
