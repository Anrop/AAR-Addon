#include "httpClient.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>

using boost::asio::ip::tcp;
using namespace std;

httpClient::httpClient() {
}

httpClient::httpClient(const string& host, const string& url, const string& authorization, const string& data) {
    string httpData = generateHttpPost(host, url, authorization, data);
    httpPost(host, httpData);
}

string httpClient::generateHttpPost(const string& host, const string& url, const string& authorization, const string& data) {
    int content_length = data.length();
    string headers = "Host: " + host + "\r\n" +
        "Connection: close\r\n" +
        "Content-Type: application/json\r\n" +
        "Content-Length: " + std::to_string(content_length) + "\r\n";

    if (authorization.length() > 0) {
        headers = headers + "Authorization: " + authorization + "\r\n";
    }

    string request = "POST " + url + " HTTP/1.1\r\n" +
        headers +
        "\r\n" +
        data;

    return request;
}

void httpClient::parseData(const string& data) {
    if (!data.empty()) {
        string dataWithoutCarriageReturn = boost::replace_all_copy(data, "\r", "");
        httpClient::status = (status_t)boost::lexical_cast<int>(dataWithoutCarriageReturn.substr(9, 3));
        bool chunked = (dataWithoutCarriageReturn.find("Transfer-Encoding: chunked\n") < string::npos) ? true : false;

        size_t headerEnd = (dataWithoutCarriageReturn.find("\n\n") + 2);
        string dataWithoutHeader = dataWithoutCarriageReturn.substr(headerEnd, data.length());

        if (chunked) {
            string dataWithoutChunk = dataWithoutHeader.substr(dataWithoutHeader.find("\n")+1, dataWithoutHeader.length());
            dataWithoutChunk = dataWithoutChunk.substr(0, dataWithoutChunk.length() - 3);
            dataWithoutHeader = dataWithoutChunk;
        }

        boost::trim_right_if(dataWithoutHeader, boost::is_any_of("\n"));

        httpClient::output = dataWithoutHeader;
    }
}

void httpClient::httpPost(const string& host, const string& data) {
    try {
        boost::asio::io_service io_service;

        tcp::resolver resolver(io_service);
        tcp::resolver::query query(host, "80");
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

        tcp::socket socket(io_service);
        boost::asio::connect(socket, endpoint_iterator);

        boost::system::error_code ignored_error;
        boost::asio::write(socket, boost::asio::buffer( data ), ignored_error);

    		httpClient::output.clear();
    		string buffer;

        for (;;)
        {
            boost::array<char, 128> buf;
            boost::system::error_code error;

            size_t len = socket.read_some(boost::asio::buffer(buf), error);

            if (error == boost::asio::error::eof)
                break;
            else if (error)
                throw boost::system::system_error(error);

            for (int i=0; i<len; i++) {
                buffer += buf[i];
            }
        }

        httpClient::parseData(buffer);
    }
    catch(boost::system::system_error& e)
    {
        status = httpClient::CONNECTION_FAILED;
    }
}

string httpClient::getResult() {
	return output;
}
