#include "../catch.hpp"
#include <EventManager.hpp>

SCENARIO( "EventManager can add event", "[EventManager]" ) {

    GIVEN( "An empty EventManager" ) {
        EventManager *em = new EventManager;

        REQUIRE( em->isEmpty() );

        WHEN( "and event is added" ) {
            em->addEvent( "test=test" );

            THEN( "it contains one item and is no longer empty" ) {
                REQUIRE( em->count() == 1 );
                REQUIRE( !em->isEmpty() );
            }
        }
    }
}
