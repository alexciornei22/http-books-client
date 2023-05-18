#ifndef HTTP_BOOKS_CLIENT_HTTPRESPONSE_HPP
#define HTTP_BOOKS_CLIENT_HTTPRESPONSE_HPP

#include <string>
#include <unordered_map>
#include <nlohmann/json.hpp>

class HTTPResponse {
public:
    HTTPResponse() = default;
    explicit HTTPResponse(const std::string& response);
    int getStatusCode() const;
    const std::string &getStatusText() const;
    const nlohmann::json &getJsonData() const;
    const std::unordered_map<std::string, std::string> &getCookies() const;

    void printStatus();

private:
    std::string protocol_version;
    int status_code = 0;
    std::string status_text;
    nlohmann::json json_data;
    std::unordered_map<std::string, std::string> cookies;
};


#endif //HTTP_BOOKS_CLIENT_HTTPRESPONSE_HPP
