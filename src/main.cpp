#include <iostream>
#include <string>
#include <ConsoleCommands.hpp>

using namespace std;

int main() {
    // main communication loop
    while (true) {
        string command_string;
        getline(cin, command_string);

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
