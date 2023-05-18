#include <SessionData.hpp>

using namespace std;

const std::string SessionData::server_ip = "34.254.242.81";
const int SessionData::port = 8080;

SessionData& SessionData::getInstance() {
    static SessionData instance;

    return instance;
}

void SessionData::setToken(const std::string &token) {
    SessionData::token = token;
}

void SessionData::setSockfd(int sockfd) {
    SessionData::sockfd = sockfd;
}

const std::string &SessionData::getToken() const {
    return token;
}

int SessionData::getSockfd() const {
    return sockfd;
}

void SessionData::insertCookie(const string& key, std::string value) {
    cookies.insert_or_assign(key, value);
}

const unordered_map<std::string, std::string> &SessionData::getCookies() const {
    return cookies;
}
