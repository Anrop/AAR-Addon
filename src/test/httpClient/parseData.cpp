#include "../catch.hpp"
#include <httpClient.hpp>

SCENARIO( "httpClient can parse response", "[httpClient]" ) {

    GIVEN( "An httpClient" ) {
        httpClient client;

        WHEN( "a response with newlines is parsed" ) {
            std::string data = std::string("{") +
                "\"id\":1," +
                "\"name\":\"test\"," +
                "\"world\":null," +
                "\"created_at\":\"2016-03-06T12:36:59.880Z\"," +
                "\"updated_at\":\"2016-03-06T12:36:59.880Z\"" +
            "}";

            std::string response = std::string("HTTP/1.1 201 Created\n") +
                "X-Frame-Options: SAMEORIGIN\n" +
                "X-XSS-Protection: 1; mode=block\n" +
                "X-Content-Type-Options: nosniff\n" +
                "Location: http://localhost/missions/1\n" +
                "Content-Type: application/json; charset=utf-8\n" +
                "ETag: W/\"7b7c275f503b9c32bbaa534d3962d7bf\"\n" +
                "Cache-Control: max-age=0, private, must-revalidate\n" +
                "X-Request-Id: 5e99180b-5034-493f-bc4d-6543ed27b605\n" +
                "X-Runtime: 0.005779\n" +
                "\n" +
                data + "\n";


            client.parseData(response);

            THEN( "it is a valid response" ) {
                REQUIRE( client.status == httpClient::OK );
                REQUIRE( client.getResult() == data );
            }
        }

        WHEN( "a response with carriage returns and newlines is parsed" ) {
            std::string data = std::string("{") +
                "\"id\":1," +
                "\"name\":\"test\"," +
                "\"world\":null," +
                "\"created_at\":\"2016-03-06T12:36:59.880Z\"," +
                "\"updated_at\":\"2016-03-06T12:36:59.880Z\"" +
            "}";

            std::string response = std::string("HTTP/1.1 201 Created\r\n") +
                "X-Frame-Options: SAMEORIGIN\r\n" +
                "X-XSS-Protection: 1; mode=block\r\n" +
                "X-Content-Type-Options: nosniff\r\n" +
                "Location: http://localhost/missions/1\r\n" +
                "Content-Type: application/json; charset=utf-8\r\n" +
                "ETag: W/\"7b7c275f503b9c32bbaa534d3962d7bf\"\r\n" +
                "Cache-Control: max-age=0, private, must-revalidate\r\n" +
                "X-Request-Id: 5e99180b-5034-493f-bc4d-6543ed27b605\r\n" +
                "X-Runtime: 0.005779\r\n" +
                "\r\n" +
                data + "\r\n";


            client.parseData(response);

            THEN( "it is a valid response" ) {
                REQUIRE( client.status == httpClient::OK );
                REQUIRE( client.getResult() == data );
            }
        }

        WHEN( "a chunked response with newlines is parsed" ) {
            std::string data = std::string("{") +
                "\"id\":1," +
                "\"name\":\"test\"," +
                "\"world\":null," +
                "\"created_at\":\"2016-03-06T12:36:59.880Z\"," +
                "\"updated_at\":\"2016-03-06T12:36:59.880Z\"" +
            "}";

            std::string response = std::string("HTTP/1.1 201 Created\n") +
                "X-Frame-Options: SAMEORIGIN\n" +
                "X-XSS-Protection: 1; mode=block\n" +
                "X-Content-Type-Options: nosniff\n" +
                "Location: http://localhost/missions/1\n" +
                "Content-Type: application/json; charset=utf-8\n" +
                "ETag: W/\"7b7c275f503b9c32bbaa534d3962d7bf\"\n" +
                "Cache-Control: max-age=0, private, must-revalidate\n" +
                "X-Request-Id: 5e99180b-5034-493f-bc4d-6543ed27b605\n" +
                "X-Runtime: 0.005779\n" +
                "Transfer-Encoding: chunked\n" +
                "\n" +
                "73\n" +
                data + "\n" +
                "0\n";


            client.parseData(response);

            THEN( "it is a valid response" ) {
                REQUIRE( client.status == httpClient::OK );
                REQUIRE( client.getResult() == data );
            }
        }

        WHEN( "a chunked response with carriage returns and newlines is parsed" ) {
            std::string data = std::string("{") +
                "\"id\":1," +
                "\"name\":\"test\"," +
                "\"world\":null," +
                "\"created_at\":\"2016-03-06T12:36:59.880Z\"," +
                "\"updated_at\":\"2016-03-06T12:36:59.880Z\"" +
            "}";

            std::string response = std::string("HTTP/1.1 201 Created\r\n") +
                "X-Frame-Options: SAMEORIGIN\r\n" +
                "X-XSS-Protection: 1; mode=block\r\n" +
                "X-Content-Type-Options: nosniff\r\n" +
                "Location: http://localhost/missions/1\r\n" +
                "Content-Type: application/json; charset=utf-8\r\n" +
                "ETag: W/\"7b7c275f503b9c32bbaa534d3962d7bf\"\r\n" +
                "Cache-Control: max-age=0, private, must-revalidate\r\n" +
                "X-Request-Id: 5e99180b-5034-493f-bc4d-6543ed27b605\r\n" +
                "X-Runtime: 0.005779\r\n" +
                "Transfer-Encoding: chunked\r\n" +
                "\r\n" +
                "73\r\n" +
                data + "\r\n" +
                "0\r\n";


            client.parseData(response);

            THEN( "it is a valid response" ) {
                REQUIRE( client.status == httpClient::OK );
                REQUIRE( client.getResult() == data );
            }
        }
    }
}
