#ifndef HTTP_BOOKS_CLIENT_HTTPCLIENT_HPP
#define HTTP_BOOKS_CLIENT_HTTPCLIENT_HPP

#include <HTTPRequest.hpp>

class HTTPClient {
public:
    static const std::string &getToken();
    static void setToken(const std::string &token);
    static void eraseToken();

    static void sendToServer(int sockfd, HTTPRequest* request);
    static std::string recvFromServer(int sockfd);

private:
    static std::string token;
    static const std::string CONTENT_LENGTH_HEADER;
    static const size_t BUFFER_SIZE;

    static size_t getContentLength(const std::string& response);
    static size_t getHeaderLength(const std::string& response);
};


#endif //HTTP_BOOKS_CLIENT_HTTPCLIENT_HPP
