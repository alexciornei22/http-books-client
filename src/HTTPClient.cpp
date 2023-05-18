#include <sys/socket.h>
#include <system_error>
#include <iostream>
#include <HTTPClient.hpp>
#include <SessionData.hpp>

using namespace std;

const string HTTPClient::CONTENT_LENGTH_HEADER = "Content-Length: ";
const string HTTPClient::CONTENT_TYPE_JSON_HEADER = "Content-Type: application/json";
const string HTTPClient::LINE_SEPARATOR = "\r\n";
const string HTTPClient::HEADER_TERMINATOR = "\r\n\r\n";
const size_t HTTPClient::BUFFER_SIZE = 1024;

HTTPResponse* HTTPClient::sendToServer(HTTPRequest *request) {
    SessionData* data = SessionData::getInstance();
    int sockfd = data->getSockfd();

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

    return recvFromServer();
}

HTTPResponse* HTTPClient::recvFromServer() {
    SessionData* data = SessionData::getInstance();
    int sockfd = data->getSockfd();

    char buffer[BUFFER_SIZE];
    size_t bytes_read = 0;
    string response;

    do {
        ssize_t bytes = recv(sockfd, buffer, BUFFER_SIZE, 0);

        if (bytes < 0)
            throw system_error(errno, generic_category(), "recv()");

        bytes_read += bytes;

        response.append(buffer, bytes);
    } while (response.find(HTTPClient::HEADER_TERMINATOR) == string::npos);

    size_t content_length = getContentLength(response);
    size_t header_length = getHeaderLength(response);
    size_t total = content_length + header_length;

    while (bytes_read < total) {
        ssize_t bytes = recv(sockfd, buffer, BUFFER_SIZE, 0);

        if (bytes < 0)
            throw system_error(errno, generic_category(), "recv()");

        bytes_read += bytes;

        response.append(buffer, bytes);
    }

    return new HTTPResponse(response);
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
