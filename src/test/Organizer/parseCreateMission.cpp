#include "../catch.hpp"
#include <Organizer.hpp>

SCENARIO( "Organizer can parse mission response", "[Organizer]" ) {

    GIVEN( "An Organizer" ) {
        Organizer organizer;

        WHEN( "a response with mission id as string" ) {
            std::string response = std::string("{") +
                "\"id\":\"1\"," +
                "\"name\":\"name\"," +
                "\"world\":\"world\"," +
                "\"created_at\":\"2016-03-06T12:36:59.880Z\"," +
                "\"updated_at\":\"2016-03-06T12:36:59.880Z\"" +
            "}";

            Organizer::status_response status = organizer.parseCreateMission(response);

            THEN( "it is a valid status" ) {
                REQUIRE( status == Organizer::OK );
            }

            THEN( "it has correct mission id" ) {
              REQUIRE( organizer.getMissionId() == "1" );
            }
        }

        WHEN( "a response with mission id as int" ) {
            std::string response = std::string("{") +
                "\"id\":1," +
                "\"name\":\"name\"," +
                "\"world\":\"world\"," +
                "\"created_at\":\"2016-03-06T12:36:59.880Z\"," +
                "\"updated_at\":\"2016-03-06T12:36:59.880Z\"" +
            "}";

            Organizer::status_response status = organizer.parseCreateMission(response);

            THEN( "it is a valid status" ) {
                REQUIRE( status == Organizer::OK );
            }

            THEN( "it has correct mission id" ) {
              REQUIRE( organizer.getMissionId() == "1" );
            }
        }

        WHEN( "an invalid response" ) {
            std::string response = std::string("{\"id\":1");

            Organizer::status_response status = organizer.parseCreateMission(response);

            THEN( "it is a parse error" ) {
                REQUIRE( status == Organizer::PARSE_ERROR );
            }
        }
    }
}
