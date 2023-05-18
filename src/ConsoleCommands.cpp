#include <ConsoleCommands.hpp>
#include <HTTPRequest.hpp>
#include <HTTPClient.hpp>
#include <iostream>
#include <SessionData.hpp>

using namespace std;

const std::string ConsoleCommand::ENDPOINT = "/api/v1/tema/";

ConsoleCommand* CommandFactory::getCommand(const string& command) {
    if (command == "exit")
        throw exited();
    if (command == "register")
        return new RegisterCommand();
    if (command == "login")
        return new LoginCommand();

    return new InvalidCommand();
}

string ConsoleCommand::promptInput(const string& prompt) {
    cout << prompt << "=";

    string input;
    cin >> input;
    return input;
}

void InvalidCommand::execute() {
    cout << "Invalid Command!" << endl;
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

    delete request;
    delete response;
}

void LoginCommand::execute() {
    username = promptInput("username");
    password = promptInput("password");
    data["password"] = password;
    data["username"] = username;

    string path = ENDPOINT + "auth/login";
    auto* request = new HTTPRequest("POST", path);
    request->setJson(data);

    HTTPResponse* response = HTTPClient::sendToServer(request);

    SessionData& ses = SessionData::getInstance();
    cout << "cookies" << endl;
    for (const auto& cookie : ses.getCookies()) {
        cout << cookie.first << " " << cookie.second << endl;
    }
    delete request;
    delete response;
}
