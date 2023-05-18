#ifndef HTTP_BOOKS_CLIENT_SESSIONDATA_HPP
#define HTTP_BOOKS_CLIENT_SESSIONDATA_HPP

#include <string>

class SessionData {
public:
    static SessionData & getInstance();
    void setToken(const std::string &token);
    void setConnectCookie(const std::string &connectCookie);
    void setSockfd(int sockfd);

    static const std::string server_ip;
    static const int port;

public:
    const std::string &getToken() const;
    const std::string &getConnectCookie() const;
    int getSockfd() const;

private:
    std::string token;
    std::string connect_cookie;
    int sockfd;

    SessionData() = default;
    SessionData(const SessionData&) = default;
};

#endif //HTTP_BOOKS_CLIENT_SESSIONDATA_HPP
