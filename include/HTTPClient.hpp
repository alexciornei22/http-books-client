#ifndef HTTP_BOOKS_CLIENT_HTTPCLIENT_HPP
#define HTTP_BOOKS_CLIENT_HTTPCLIENT_HPP

#include <HTTPRequest.hpp>
#include <HTTPResponse.hpp>

class HTTPClient {
public:
    static HTTPResponse* sendToServer(HTTPRequest *request);
    static HTTPResponse* recvFromServer();

    static size_t getContentLength(const std::string& response);
    static size_t getHeaderLength(const std::string& response);

    static const std::string CONTENT_LENGTH_HEADER;
    static const std::string CONTENT_TYPE_JSON_HEADER;
    static const std::string SET_COOKIE_HEADER;
    static const std::string LINE_SEPARATOR;
    static const std::string HEADER_TERMINATOR;
    static const size_t BUFFER_SIZE;
};


#endif //HTTP_BOOKS_CLIENT_HTTPCLIENT_HPP
