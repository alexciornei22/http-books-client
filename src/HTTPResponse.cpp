#include <HTTPResponse.hpp>
#include <sstream>

using namespace std;

const std::string &HTTPResponse::getStatusText() const {
    return status_text;
}

int HTTPResponse::getStatusCode() const {
    return status_code;
}

HTTPResponse::HTTPResponse(const string& response) {
    stringstream stream(response);

    stream >> protocol_version;
    stream >> status_code;

    stream.get();
    getline(stream, status_text);
    status_text.pop_back();
}
