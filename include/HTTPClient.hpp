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
};


#endif //HTTP_BOOKS_CLIENT_HTTPCLIENT_HPP
