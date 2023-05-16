#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>

#include <iostream>
#include <cstring>
#include <string>
#include <array>

using namespace std;

class exited : public exception {};

int open_connection(const char *host_ip, int portno, int ip_type, int socket_type, int flag)
{
    sockaddr_in serv_addr = sockaddr_in();
    int sockfd = socket(ip_type, socket_type, flag);
    if (sockfd < 0)
        throw system_error(errno, generic_category(), "socket()");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = ip_type;
    serv_addr.sin_port = htons(portno);
    inet_aton(host_ip, &serv_addr.sin_addr);

    /* connect the socket */
    if (connect(sockfd, (sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
        throw system_error(errno, generic_category(), "connect()");

    return sockfd;
}

void get_console_input() {
    string command;
    cin >> command;

    if (command == "exit") {
        throw exited();
    }

}

void check_polls(array<pollfd, 2> poll_fds) {
    for (auto pfd: poll_fds) {
        if (!(pfd.revents & POLLIN))
            continue;

        if (pfd.fd == STDIN_FILENO) {
            get_console_input();
        } else {

        }
    }
}

int main() {
    // server data
    const string ip = "34.254.242.81";
    const int port = 8080;

    int sockfd = open_connection(ip.c_str(), port, AF_INET, SOCK_STREAM, 0);

    array<pollfd, 2> poll_fds = {
            pollfd{STDIN_FILENO, POLLIN, 0},
            pollfd{sockfd, POLLIN, 0}
    };

    // main communication loop
    while (true) {
        int ret = poll(poll_fds.data(), poll_fds.size(), -1);
        if (ret < 0)
            throw system_error(errno, generic_category(), "poll()");

        try {
            check_polls(poll_fds);
        } catch (exited &e) {
            break;
        }
    }

    return 0;
}
