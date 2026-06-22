#include "response.hpp"
#include <sstream>

std::string build_response(const Response& response)
{
    std::ostringstream ss;

    ss << "HTTP/1.1 " << response.status_code << " " << response.status_text
       << "\r\n";

    ss << "Content-Type: " << response.content_type << "\r\n";

    ss << "Content-Length: " << response.body.size() << "\r\n";

    ss << "Connection: close\r\n";

    ss << "\r\n";

    ss << response.body;

    return ss.str();
}
