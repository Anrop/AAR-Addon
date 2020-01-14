#pragma once

#include <string>

/* */
/* TODO: Add authorization code in http header */
class httpClient {
public:
    httpClient();
    httpClient(const std::string& host, const std::string& url, const std::string& authorization, const std::string& data);
    std::string generateHttpPost(const std::string& host, const std::string& url, const std::string& authorization, const std::string& data);
    std::string getResult();
    void httpPost(const std::string& host, const std::string& data);
    void parseData(const std::string& data);

    enum status_t { OK = 201, BAD_REQUEST = 400, UNAUTHORIZED = 401, FORBIDDEN = 403, NOT_FOUND = 404, CONNECTION_FAILED = 1000 };
    status_t status;
private:
    std::string output;
};
