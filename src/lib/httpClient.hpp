#include "common.h"

using namespace std;
using boost::asio::ip::tcp;

/* */
/* TODO: Add authorization code in http header */
class httpClient {
public:
    httpClient(const string& url, const string& data);
    httpClient(const string& host, const string& url, const string& data);
    string getResult();

    enum status_t { OK = 201, BAD_REQUEST = 400, UNAUTHORIZED = 401, FORBIDDEN = 403, NOT_FOUND = 404, CONNECTION_FAILED = 1000 };
    status_t status;
private:
    void httpPost(const string& host, const string& data);
    void parseData(const string& data);
    string generateHttpPost(const string& host, const string& url, const string& data);
    string output;
};
