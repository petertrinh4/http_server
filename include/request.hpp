#pragma once

#include <string>

struct Request
{
    std::string method;
    std::string path;
    std::string version;
};

Request parse_request(const std::string& request_text);
