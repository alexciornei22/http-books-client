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

int main() {
    // main communication loop
    while (true) {
        string command_string;
        cin >> command_string;

        try {
            ConsoleCommand *command = CommandFactory::getCommand(command_string);
            command->execute();

            delete command;
        } catch (exited &e) {
            break;
        }
    }

    return 0;
}
