#include <HTTPClient.hpp>
#include <sys/socket.h>
#include <system_error>
#include <iostream>

using namespace std;

string HTTPClient::token;

void HTTPClient::sendToServer(int sockfd, HTTPRequest *request) {
    int bytes, sent = 0;
    string message = request->serializeToString();
    int total = message.size();

    cout << message << "\n";

    do
    {
        bytes = send(sockfd, message.c_str() + sent, total - sent, 0);
        if (bytes < 0)
            throw system_error(errno, generic_category(), "send()");

        sent += bytes;
    } while (sent < total);

}

const string &HTTPClient::getToken() {
    return token;
}

void HTTPClient::setToken(const string &token) {
    HTTPClient::token = token;
}

void HTTPClient::eraseToken() {
    token.erase();
}

std::string HTTPClient::recvFromServer(int sockfd) {
    char response[1500];
    char *aux = response;

    do {
        int bytes = recv(sockfd, aux, 1500, 0);

        if (bytes < 0){
            throw system_error(errno, generic_category(), "recv()");
        }

        if (bytes == 0) {
            cout << "0" << "\n";
            break;
        }
        aux += bytes;
        string res = response;

        if (res.find_last_of("\r\n") != string::npos)
            break;
        else
            cout << res << "\n";
    } while (true);

    return string(response);
}
