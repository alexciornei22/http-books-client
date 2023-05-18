#ifndef HTTP_BOOKS_CLIENT_HTTPREQUEST_HPP
#define HTTP_BOOKS_CLIENT_HTTPREQUEST_HPP

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

class HTTPRequest {
public:
    HTTPRequest(std::string method, std::string path);
    void setMethod(const std::string &method);
    void setPath(const std::string &path);
    void setHeaders(const std::vector<std::string> &headers);

    std::string serializeToString();

private:
    std::string method;
    std::string path;
    std::vector<std::string> headers;
    nlohmann::json json_data;
public:
    const nlohmann::json &getJsonData() const;

public:
    void setJson(const nlohmann::json &json);
};


#endif //HTTP_BOOKS_CLIENT_HTTPREQUEST_HPP
