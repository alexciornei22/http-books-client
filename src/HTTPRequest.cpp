#include <HTTPRequest.hpp>
#include <HTTPClient.hpp>

using namespace std;

void HTTPRequest::setMethod(const string &method) {
    HTTPRequest::method = method;
}

void HTTPRequest::setPath(const string &path) {
    HTTPRequest::path = path;
}

void HTTPRequest::setJson(const nlohmann::json &json) {
    HTTPRequest::json_data = json;
}

void HTTPRequest::setHeaders(const vector<string> &headers) {
    HTTPRequest::headers = headers;
}

string HTTPRequest::serializeToString() {
    string request;
    string content;

    request += method + " ";
    request += path + " ";
    request += "HTTP/1.1" + HTTPClient::LINE_SEPARATOR;

    if (!json_data.empty()) {
        content = json_data.dump();

        request += HTTPClient::CONTENT_TYPE_JSON_HEADER
                + HTTPClient::LINE_SEPARATOR;
        request += HTTPClient::CONTENT_LENGTH_HEADER
                + to_string(content.length()) + HTTPClient::LINE_SEPARATOR;
    }
    request += HTTPClient::LINE_SEPARATOR; // end of header

    request += content;
    return request;
}

HTTPRequest::HTTPRequest(std::string method, std::string path) {
    HTTPRequest::method = method;
    HTTPRequest::path = path;
}

const nlohmann::json &HTTPRequest::getJsonData() const {
    return json_data;
}
