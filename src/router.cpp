#include "router.hpp"
#include "file_server.hpp"
#include <filesystem>
#include <string>

Response route(const Request& request)
{
    // 1. API-style routes
    if (request.path == "/hello")
    {
        return {200, "OK", "Hello World"};
    }

    std::string path = request.path;

    // 2. Default route
    if (path == "/")
    {
        path = "/index.html";
    }

    // 3. PATH TRAVERSAL PROTECTION (IMPORTANT)
    if (path.find("..") != std::string::npos)
    {
        return {403, "Forbidden", "403 Forbidden"};
    }

    // 4. Build full file path safely
    std::string file_path = "public" + path;

    std::string body = load_file(file_path);

    if (body.empty())
    {
        return {404, "Not Found", "404 Not Found"};
    }

    return {200, "OK", body, get_mime_type(file_path)};
}
