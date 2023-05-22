#include <InputValidator.hpp>
#include <algorithm>
#include <iostream>

using namespace std;

bool InputValidator::validate(const string &input) {
    return true;
}

bool NoSpacesValidator::validate(const string &input) {
    return input.find(' ') == string::npos && !input.empty();
}

void NoSpacesValidator::printErrorMessage() {
    cout << "No spaces allowed! Command canceled!" << endl;
}

bool NumberValidator::validate(const string &input) {
    return all_of(input.begin(), input.end(), [](char ch) { return isdigit(ch); })
           && !input.empty();
}

void NumberValidator::printErrorMessage() {
    cout << "Input must be a number! Command canceled!" << endl;
}
