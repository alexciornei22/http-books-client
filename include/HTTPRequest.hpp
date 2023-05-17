#ifndef HTTP_BOOKS_CLIENT_HTTPREQUEST_HPP
#define HTTP_BOOKS_CLIENT_HTTPREQUEST_HPP

#include <string>
#include <vector>

class HTTPRequest {
public:
    HTTPRequest(std::string method, std::string path);
    void setMethod(const std::string &method);
    void setPath(const std::string &path);
    void setHeaders(const std::vector<std::string> &headers);
    void setToken(const std::string &token);

    std::string serializeToString();

private:
    std::string method;
    std::string path;
    std::vector<std::string> headers;
    std::string token;
    static const std::string LINE_SEPARATOR;
};


#endif //HTTP_BOOKS_CLIENT_HTTPREQUEST_HPP
