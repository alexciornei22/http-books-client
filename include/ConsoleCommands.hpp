#ifndef HTTP_BOOKS_CLIENT_CONSOLECOMMANDS_HPP
#define HTTP_BOOKS_CLIENT_CONSOLECOMMANDS_HPP

#include <nlohmann/json.hpp>
#include <HTTPResponse.hpp>
#include <InputValidator.hpp>

using json = nlohmann::json;

class exited : public std::exception {};

class ConsoleCommand {
public:
    virtual ~ConsoleCommand() = default;
    virtual void execute() {};

protected:
    static std::string promptInput(const std::string& prompt);
    static std::string promptInput(const std::string& prompt, InputValidator* validator);

    static const std::string ENDPOINT;
    json data;
};

class CommandFactory {
public:
    static ConsoleCommand* getCommand(const std::string& command);
};

class RegisterCommand : public ConsoleCommand {
public:
    void execute() override;

private:
    std::string username;
    std::string password;
};

class LoginCommand : public ConsoleCommand {
public:
    void execute() override;

private:
    std::string username;
    std::string password;
};

class AccessCommand : public ConsoleCommand {
public:
    void execute() override;
};

class GetBooksCommand : public ConsoleCommand {
public:
    void execute() override;
};

class GetBookCommand : public ConsoleCommand {
public:
    void execute() override;

private:
    std::string id;
};

class AddBookCommand : public ConsoleCommand {
public:
    void execute() override;

private:
    std::string title;
    std::string author;
    std::string genre;
    int page_count;
    std::string publisher;
};

class DeleteBookCommand : public ConsoleCommand {
public:
    void execute() override;

private:
    std::string id;
};

class LogoutCommand : public ConsoleCommand {
public:
    void execute() override;
};

class InvalidCommand : public ConsoleCommand {
    void execute() override;
};
#endif //HTTP_BOOKS_CLIENT_CONSOLECOMMANDS_HPP
