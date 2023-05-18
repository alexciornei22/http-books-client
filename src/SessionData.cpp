#include <SessionData.hpp>

SessionData* SessionData::instance = nullptr;
const std::string SessionData::server_ip = "34.254.242.81";
const int SessionData::port = 8080;

SessionData *SessionData::getInstance() {
    if (instance == nullptr)
        instance = new SessionData();

    return instance;
}

void SessionData::setToken(const std::string &token) {
    SessionData::token = token;
}

void SessionData::setConnectCookie(const std::string &connectCookie) {
    connect_cookie = connectCookie;
}

void SessionData::setSockfd(int sockfd) {
    SessionData::sockfd = sockfd;
}

const std::string &SessionData::getToken() const {
    return token;
}

const std::string &SessionData::getConnectCookie() const {
    return connect_cookie;
}

int SessionData::getSockfd() const {
    return sockfd;
}
