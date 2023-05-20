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
    if (command == "get_books")
        return new GetBooksCommand();
    if (command == "get_book")
        return new GetBookCommand();
    if (command == "add_book")
        return new AddBookCommand();
    if (command == "delete_book")
        return new DeleteBookCommand();
    if (command == "logout")
        return new LogoutCommand();

    return new InvalidCommand();
}

string ConsoleCommand::promptInput(const string& prompt) {
    cout << prompt << "=";

    string input;
    getline(cin, input);
    return input;
}

std::string ConsoleCommand::promptInput(const string &prompt, InputValidator* validator) {
    cout << prompt << "=";

    string input;
    getline(cin, input);

    if (!validator->validate(input))
        throw invalid_input();

    return input;
}

void InvalidCommand::execute() {
    cout << "Invalid Command!" << endl;
}

void RegisterCommand::execute() {
    NoSpacesValidator validator;

    try {
        username = promptInput("username", &validator);
        password = promptInput("password");
    } catch (invalid_input &e) {
        validator.printErrorMessage();
        return;
    }

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
    NoSpacesValidator validator;

    try {
        username = promptInput("username", &validator);
        password = promptInput("password");
    } catch (invalid_input &e) {
        validator.printErrorMessage();
        return;
    }

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

        SessionData& data = SessionData::getInstance();
        data.setToken(response->getJsonData()["token"]);
    } else {
        string error = response->getJsonData()["error"];
        cout << error << endl;
    }

    delete request;
    delete response;
}

void GetBooksCommand::execute() {
    string path = ENDPOINT + "library/books";
    auto* request = new HTTPRequest("GET", path);

    HTTPResponse* response = HTTPClient::sendToServer(request);

    response->printStatus();
    switch (response->getStatusCode()) {
        case 200:
            for (auto const& book : response->getJsonData()) {
                cout << "Book id=" << book["id"] << endl;
                cout << "title=" << book["title"] << endl;
            }
            break;
        case 403:
            cout << "You do not have access to the library!" << endl;
            break;
        default:
            string error = response->getJsonData()["error"];
            cout << error << endl;
            break;
    }
    delete request;
    delete response;
}

void GetBookCommand::execute() {
    NumberValidator validator;

    try {
        id = promptInput("id", &validator);
    } catch (invalid_input &e) {
        validator.printErrorMessage();
        return;
    }

    data["id"] = id;

    string path = ENDPOINT + "library/books/" + id;
    auto* request = new HTTPRequest("GET", path);

    HTTPResponse* response = HTTPClient::sendToServer(request);
    json json_response = response->getJsonData();

    response->printStatus();
    switch (response->getStatusCode()) {
        case 200:
            cout << "Book id=" << id << endl;
            cout << "title=" << json_response["title"] << endl;
            cout << "author=" << json_response["author"] << endl;
            cout << "publisher=" << json_response["publihser"] << endl;
            cout << "genre=" << json_response["genre"] << endl;
            cout << "page_count=" << json_response["page_count"] << endl;
            break;
        case 403:
            cout << "You do not have access to the library!" << endl;
            break;
        case 404:
            cout << "The book with id: " << id << " was not found!" << endl;
            break;
        default:
            string error = response->getJsonData()["error"];
            cout << error << endl;
            break;
    }

    delete request;
    delete response;
}

void AddBookCommand::execute() {
    NumberValidator validator;

    try {
        title = promptInput("title");
        author = promptInput("author");
        genre = promptInput("genre");
        page_count = stoi(promptInput("page_count", &validator));
        publisher = promptInput("publisher");
    } catch (invalid_input &e) {
        validator.printErrorMessage();
        return;
    }

    data["title"] = title;
    data["author"] = author;
    data["genre"] = genre;
    data["page_count"] = page_count;
    data["publisher"] = publisher;

    string path = ENDPOINT + "library/books";
    auto* request = new HTTPRequest("POST", path);
    request->setJson(data);

    HTTPResponse* response = HTTPClient::sendToServer(request);

    response->printStatus();
    if (response->getStatusCode() == 200) {
        cout << "Book added succesfully!" << endl;
    } else {
        string error = response->getJsonData()["error"];
        cout << error << endl;
    }

    delete request;
    delete response;
}

void DeleteBookCommand::execute() {
    NumberValidator validator;

    try {
        id = promptInput("id", &validator);
    } catch (invalid_input &e) {
        validator.printErrorMessage();
        return;
    }

    data["id"] = id;

    string path = ENDPOINT + "library/books/" + id;
    auto* request = new HTTPRequest("DELETE", path);

    HTTPResponse* response = HTTPClient::sendToServer(request);

    response->printStatus();
    switch (response->getStatusCode()) {
        case 200:
            cout << "Book with id: " << id << " was deleted succesfully!" << endl;
            break;
        case 403:
            cout << "You do not have access to the library!" << endl;
            break;
        case 404:
            cout << "The book with id: " << id << " was not found!" << endl;
            break;
        default:
            string error = response->getJsonData()["error"];
            cout << error << endl;
            break;
    }

    delete request;
    delete response;
}

void LogoutCommand::execute() {

    string path = ENDPOINT + "auth/logout";
    auto* request = new HTTPRequest("GET", path);

    HTTPResponse* response = HTTPClient::sendToServer(request);

    SessionData& data = SessionData::getInstance();
    data.deleteCookies();
    data.deleteToken();

    response->printStatus();
    switch (response->getStatusCode()) {
        case 200:
            cout << "Logged out succesfully!" << endl;
            break;
        default:
            string error = response->getJsonData()["error"];
            cout << error << endl;
            break;
    }

    delete request;
    delete response;
}
