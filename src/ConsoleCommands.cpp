#include <ConsoleCommands.hpp>
#include <HTTPRequest.hpp>
#include <HTTPClient.hpp>
#include <iostream>

using namespace std;

const std::string ConsoleCommand::ENDPOINT = "/api/v1/tema/";

ConsoleCommand* CommandFactory::getCommand(const string& command) {
    if (command == "exit")
        throw exited();
    if (command == "register")
        return new RegisterCommand();

    return new InvalidCommand();
}

string ConsoleCommand::promptInput(const string& prompt) {
    cout << prompt << "=";

    string input;
    cin >> input;
    return input;
}

void RegisterCommand::execute() {
    username = promptInput("username");
    password = promptInput("password");
    data["password"] = password;
    data["username"] = username;

    string path = ENDPOINT + "auth/register";
    auto* request = new HTTPRequest("POST", path);
    request->setJson(data);

    HTTPResponse* response = HTTPClient::sendToServer(request);

    cout << "json dump" << response->getJsonData().dump() << endl;

    delete request;
    delete response;
}

void InvalidCommand::execute() {
    cout << "Invalid Command!" << endl;
}