#ifndef HTTP_BOOKS_CLIENT_SESSIONDATA_HPP
#define HTTP_BOOKS_CLIENT_SESSIONDATA_HPP

#include <string>
#include <unordered_map>

class SessionData {
public:
    static SessionData& getInstance();
    void setToken(const std::string &token);
    void setSockfd(int sockfd);

    const std::string &getToken() const;
    int getSockfd() const;
    const std::unordered_map<std::string, std::string> &getCookies() const;

    void insertCookie(const std::string& key, std::string value);

    static const std::string server_ip;
    static const int port;
private:
    std::string token;
    int sockfd;
    std::unordered_map<std::string, std::string> cookies;

    SessionData() = default;
    SessionData(const SessionData&) = default;
};

#endif //HTTP_BOOKS_CLIENT_SESSIONDATA_HPP
