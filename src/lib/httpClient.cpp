#include "common.h"

using namespace std;
using boost::asio::ip::tcp;

/* */
/* TODO: Add authorization code in http header */
class httpClient {
public:
    httpClient(const string& url, const string& data);
    httpClient(const string& host, const string& url, const string& data);
    //void post(const string& url, const string& data);
    //void post(const string& host, const string& url, const string& data)
    string get_result();

    enum status_t { OK = 200, BAD_REQUEST = 400, UNAUTHORIZED = 401, FORBIDDEN = 403, NOT_FOUND = 404, CONNECTION_FAILED = 1000 };
    status_t status;
private:
    void httpPost(const string& host, const string& data);
    void parseData(const string& data);
    string generateHttpPost(const string& host, const string& url, const string& data);
    string output;
};

httpClient::httpClient(const string& url, const string& data) {
    string url_to_parse = url;
    if (url_to_parse.substr(0, 7) == "http://")
        url_to_parse = url_to_parse.substr(7, url_to_parse.length());

    string host = url_to_parse.substr(0, url_to_parse.find("/"));
    string resource = url_to_parse.substr(url_to_parse.find("/"), url_to_parse.length());

    string httpData = generateHttpPost(host, url, data);
    httpPost(host, httpData);
}

httpClient::httpClient(const string& host, const string& url, const string& data) {
    string httpData = generateHttpPost(host, url, data);
    httpPost(host, httpData);
}

/*
void httpClient::post(const string& url, const string& data) {
    string url_to_parse = url;
    if (url_to_parse.substr(0, 7) == "http://")
        url_to_parse = url_to_parse.substr(7, url_to_parse.length());

    string host = url_to_parse.substr(0, url_to_parse.find("/"));
    string resource = url_to_parse.substr(url_to_parse.find("/"), url_to_parse.length());

    string httpData = generateHttpPost(host, resource, data);
    httpPost(host, httpData);
}
*/

/* Assumes json data. Maybe get a node tree and serialize into json instead? */
string httpClient::generateHttpPost(const string& host, const string& url, const string& data) {
	/* Generate a valid HTTP POST with the data as body */

    int content_length = data.length();

    string response = "POST " + url + " HTTP/1.1\r\n" +
        "Host: " + host + "\r\n" +
	   "Connection: close\r\n" +
        "Content-Type: application/json\r\n" +
        "Content-Length: " + boost::lexical_cast<std::string>(content_length) + "\r\n" +
        "\r\n" + data;

    return response;
}

void httpClient::parseData(const string& data) {
	if (!data.empty()) {
		/* Check HTTP status (Wether its 200 OK or not) and then strip the header away and only keep the body */

        // TODO: add support for Transfer-Encoding: chunked (it adds prefix and postfix to body data)

		httpClient::status = (status_t)boost::lexical_cast<int>(data.substr(9, 3));

        bool chunked = (data.find("Transfer-Encoding: chunked\r\n") < std::string::npos) ? true : false;
        //cout << "chunked" << endl;
		size_t headerEnd = (data.find("\r\n\r\n") + 4);
		string dataWithoutHeader = data.substr(headerEnd, data.length());

        /* Strip first and last line if chunked */
        if (chunked) {
            // Remove the first line
            string dataWithoutChunk = dataWithoutHeader.substr(dataWithoutHeader.find("\r\n")+2, dataWithoutHeader.length());
            // last line should be "\r\n\r\n0\r\n\r\n"
            dataWithoutChunk = dataWithoutChunk.substr(0, dataWithoutChunk.length() - 6);
            dataWithoutHeader = dataWithoutChunk;
        }

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
    //catch (std::exception& e)
    catch(boost::system::system_error& e)
    {
        //cout << "exception caught" << endl;
        std::cerr << e.what() << std::endl;
        //cout<<"Info: "  << boost::diagnostic_information(e) <<endl;
        status = httpClient::CONNECTION_FAILED;
    }
}

string httpClient::get_result() {
	/* Strip HTTP header data from the output variable and then return it here */
	return output;
}

/*
int main()
{
	return 0;
}
*/