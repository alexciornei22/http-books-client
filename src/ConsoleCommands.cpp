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
    if (command == "enter_library")
        return new AccessCommand();

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

    response->printStatus();
    if (response->getStatusCode() == 201) {
        cout << "User registered succesfully!" << endl;
    } else {
        string error = response->getJsonData()["error"];
        cout << error << endl;
    }

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

    response->printStatus();
    switch (response->getStatusCode()) {
        case 200:
            cout << "Logged in, welcome!" << endl;
            break;
        case 204:
            cout << "You are already logged in!" << endl;
            break;
        default:
            string error = response->getJsonData()["error"];
            cout << error << endl;
            break;
    }

    delete request;
    delete response;
}

void AccessCommand::execute() {
    string path = ENDPOINT + "library/access";
    auto* request = new HTTPRequest("GET", path);

    HTTPResponse* response = HTTPClient::sendToServer(request);

    response->printStatus();
    if (response->getStatusCode() == 200) {
        cout << "Access granted!" << endl;
    } else {
        string error = response->getJsonData()["error"];
        cout << error << endl;
    }

    delete request;
    delete response;
}
