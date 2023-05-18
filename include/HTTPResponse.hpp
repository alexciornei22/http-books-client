#ifndef HTTP_BOOKS_CLIENT_HTTPRESPONSE_HPP
#define HTTP_BOOKS_CLIENT_HTTPRESPONSE_HPP

#include <string>
#include <nlohmann/json.hpp>

class HTTPResponse {
public:
    HTTPResponse() = default;
    explicit HTTPResponse(const std::string& response);
    int getStatusCode() const;
    const std::string &getStatusText() const;

private:
    std::string protocol_version;
    int status_code = 0;
    std::string status_text;
    nlohmann::json json_data;
public:
    const nlohmann::json &getJsonData() const;
};


#endif //HTTP_BOOKS_CLIENT_HTTPRESPONSE_HPP
