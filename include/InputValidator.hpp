#ifndef HTTP_BOOKS_CLIENT_INPUTVALIDATOR_HPP
#define HTTP_BOOKS_CLIENT_INPUTVALIDATOR_HPP

#include <string>

class invalid_input : public std::exception {};

class InputValidator {
public:
    virtual bool validate(const std::string& input);
    virtual void printErrorMessage() {}
};

class NoSpacesValidator : public InputValidator {
public:
    bool validate(const std::string &input) override;
    void printErrorMessage() override;
};

class NumberValidator : public InputValidator {
public:
    bool validate(const std::string &input) override;
    void printErrorMessage() override;
};

#endif //HTTP_BOOKS_CLIENT_INPUTVALIDATOR_HPP
