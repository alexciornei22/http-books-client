#include <sys/socket.h>
#include <system_error>
#include <iostream>
#include <HTTPClient.hpp>
#include <SessionData.hpp>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>

using namespace std;

const string HTTPClient::CONTENT_LENGTH_HEADER = "Content-Length: ";
const string HTTPClient::CONTENT_TYPE_JSON_HEADER = "Content-Type: application/json";
const string HTTPClient::SET_COOKIE_HEADER = "Set-Cookie: ";
const string HTTPClient::LINE_SEPARATOR = "\r\n";
const string HTTPClient::HEADER_TERMINATOR = "\r\n\r\n";
const size_t HTTPClient::BUFFER_SIZE = 1024;

int open_connection()
{
    sockaddr_in serv_addr = sockaddr_in();
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        throw system_error(errno, generic_category(), "socket()");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SessionData::port);
    inet_aton(SessionData::server_ip.c_str(), &serv_addr.sin_addr);

    /* connect the socket */
    if (connect(sockfd, (sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
        throw system_error(errno, generic_category(), "connect()");

    return sockfd;
}

HTTPResponse* HTTPClient::sendToServer(HTTPRequest *request) {
    SessionData& data = SessionData::getInstance();
    int sockfd = open_connection();
    data.setSockfd(sockfd);

    ssize_t bytes, sent = 0;
    string message = request->serializeToString();
    ssize_t total = message.length();

    do
    {
        bytes = send(sockfd, message.c_str() + sent, total - sent, 0);
        if (bytes < 0)
            throw system_error(errno, generic_category(), "send()");

        sent += bytes;
    } while (sent < total);

    HTTPResponse* response = recvFromServer();

    close(sockfd);
    return response;
}

HTTPResponse* HTTPClient::recvFromServer() {
    SessionData& data = SessionData::getInstance();
    int sockfd = data.getSockfd();

    char buffer[BUFFER_SIZE];
    size_t bytes_read = 0;
    string response_string;

    do {
        ssize_t bytes = recv(sockfd, buffer, BUFFER_SIZE, 0);

        if (bytes < 0)
            throw system_error(errno, generic_category(), "recv()");

        bytes_read += bytes;

        response_string.append(buffer, bytes);
    } while (response_string.find(HTTPClient::HEADER_TERMINATOR) == string::npos);

    size_t content_length = getContentLength(response_string);
    size_t header_length = getHeaderLength(response_string);
    size_t total = content_length + header_length;

    while (bytes_read < total) {
        ssize_t bytes = recv(sockfd, buffer, BUFFER_SIZE, 0);

        if (bytes < 0)
            throw system_error(errno, generic_category(), "recv()");

        bytes_read += bytes;

        response_string.append(buffer, bytes);
    }

    auto* response = new HTTPResponse(response_string);
    for (auto const& cookie : response->getCookies()) {
        data.insertCookie(cookie.first, cookie.second);
    }

    return response;
}

size_t HTTPClient::getContentLength(const string& response) {
    size_t content_length_start = response.find(CONTENT_LENGTH_HEADER);
    if (content_length_start == string::npos)
        return 0; // no content

    size_t content_length_end = response.find("\r\n", content_length_start);
    size_t content_length_size = content_length_end - content_length_start;

    string content_length = response.substr(content_length_start, content_length_size);
    size_t length = stoi(content_length.substr(CONTENT_LENGTH_HEADER.size()));

    return length;
}

size_t HTTPClient::getHeaderLength(const string &response) {
    return response.find(HTTPClient::HEADER_TERMINATOR)
    + HTTPClient::HEADER_TERMINATOR.size();
}
