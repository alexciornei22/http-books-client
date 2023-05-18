#include <HTTPResponse.hpp>
#include <HTTPClient.hpp>
#include <sstream>

using namespace std;
using json = nlohmann::json;

const std::string &HTTPResponse::getStatusText() const {
    return status_text;
}

int HTTPResponse::getStatusCode() const {
    return status_code;
}

const json &HTTPResponse::getJsonData() const {
    return json_data;
}

HTTPResponse::HTTPResponse(const string& response) {
    stringstream stream(response);

    stream >> protocol_version;
    stream >> status_code;

    stream.get();
    getline(stream, status_text);
    status_text.pop_back();

    size_t header_length = HTTPClient::getHeaderLength(response);
    string data = response.substr(header_length);

    json_data = json::parse(data);
}
