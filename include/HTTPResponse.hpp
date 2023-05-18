#ifndef HTTP_BOOKS_CLIENT_HTTPRESPONSE_HPP
#define HTTP_BOOKS_CLIENT_HTTPRESPONSE_HPP

#include <string>

class HTTPResponse {
public:
    explicit HTTPResponse(const std::string& response);
    int getStatusCode() const;
    const std::string &getStatusText() const;

private:
    std::string protocol_version;
    int status_code;
    std::string status_text;
};


#endif //HTTP_BOOKS_CLIENT_HTTPRESPONSE_HPP
