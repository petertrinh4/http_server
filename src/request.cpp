#include "request.hpp"

#include <sstream>
#include <stdexcept>

Request parse_request(const std::string& request_text)
{
    Request request{};

    std::istringstream stream{request_text};

    if (!(stream >> request.method >> request.path >> request.version))
    {
        throw std::runtime_error("Invalid HTTP request");
    }

    return request;
}
