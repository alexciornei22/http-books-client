#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>

#include <iostream>
#include <cstring>
#include <string>
#include <array>

#include <ConsoleCommands.hpp>
#include <SessionData.hpp>

using namespace std;

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

void get_console_input() {
    string command_string;
    cin >> command_string;

    ConsoleCommand* command = CommandFactory::getCommand(command_string);
    command->execute();

    delete command;
}

void check_polls(array<pollfd, 2> poll_fds) {
    for (auto pfd: poll_fds) {
        if (!(pfd.revents & POLLIN))
            continue;

        if (pfd.fd == STDIN_FILENO) {
            get_console_input();
        } else {
            SessionData* data = SessionData::getInstance();
            close(data->getSockfd());

            int new_sockfd = open_connection();
            data->setSockfd(new_sockfd);
            cout << "reopened conn" << endl;
        }
    }
}

int main() {
    SessionData* data = SessionData::getInstance();

    int sockfd = open_connection();
    data->setSockfd(sockfd);

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
