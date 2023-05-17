#include <HTTPRequest.hpp>

using namespace std;

const string HTTPRequest::LINE_SEPARATOR = "\r\n";

void HTTPRequest::setMethod(const string &method) {
    HTTPRequest::method = method;
}

void HTTPRequest::setPath(const string &path) {
    HTTPRequest::path = path;
}

void HTTPRequest::setHeaders(const vector<string> &headers) {
    HTTPRequest::headers = headers;
}

void HTTPRequest::setToken(const string &token) {
    HTTPRequest::token = token;
}

string HTTPRequest::serializeToString() {
    string request;

    request += method + " ";
    request += path + " ";
    request += "HTTP/1.1" + LINE_SEPARATOR;

    if (!token.empty()) {
        request += "Authorization: Bearer " + token + LINE_SEPARATOR;
    }

    request += LINE_SEPARATOR;
    return request;
}

HTTPRequest::HTTPRequest(std::string method, std::string path) {
    HTTPRequest::method = method;
    HTTPRequest::path = path;
}
