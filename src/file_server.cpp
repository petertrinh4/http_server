#include "file_server.hpp"
#include <fstream>
#include <sstream>

static bool ends_with(const std::string& str, const std::string& suffix)
{
    return str.size() >= suffix.size() &&
           str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

std::string load_file(const std::string& path)
{
    std::ifstream file(path, std::ios::binary);

    if (!file.is_open())
    {
        return "";
    }

    std::ostringstream ss;
    ss << file.rdbuf();

    return ss.str();
}

std::string get_mime_type(const std::string& path)
{
    if (ends_with(path, ".html"))
        return "text/html";

    if (ends_with(path, ".css"))
        return "text/css";

    if (ends_with(path, ".js"))
        return "application/javascript";

    if (ends_with(path, ".png"))
        return "image/png";

    if (ends_with(path, ".jpg") || ends_with(path, ".jpeg"))
        return "image/jpeg";

    return "text/plain";
}
