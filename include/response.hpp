#pragma once

#include <string>

struct Response
{
    int status_code{};
    std::string status_text;
    std::string body;
    std::string content_type{"text/plain"};
};

std::string build_response(const Response& response);
