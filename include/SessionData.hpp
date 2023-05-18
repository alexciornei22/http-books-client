#ifndef HTTP_BOOKS_CLIENT_SESSIONDATA_HPP
#define HTTP_BOOKS_CLIENT_SESSIONDATA_HPP

#include <string>

class SessionData {
public:
    static SessionData* getInstance();
    void setToken(const std::string &token);
    void setConnectCookie(const std::string &connectCookie);
    void setSockfd(int sockfd);

    static const std::string server_ip;
    static const int port;

private:
    static SessionData* instance;
public:
    const std::string &getToken() const;

    const std::string &getConnectCookie() const;

    int getSockfd() const;

private:
    std::string token;
    std::string connect_cookie;
    int sockfd;
};

#endif //HTTP_BOOKS_CLIENT_SESSIONDATA_HPP
