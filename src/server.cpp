#include "server.hpp"
#include "logger.hpp"
#include "request.hpp"
#include "response.hpp"
#include "router.hpp"

#include <arpa/inet.h>
#include <cerrno>
#include <chrono>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

Server::Server(int port) : m_port{port} {}

void Server::start()
{
    std::cout << "Starting server on port " << m_port << '\n';

    int server_fd{socket(AF_INET, SOCK_STREAM, 0)};
    if (server_fd == -1)
    {
        std::cerr << "socket failed: " << std::strerror(errno) << '\n';
        return;
    }

    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(m_port);

    if (bind(server_fd, reinterpret_cast<sockaddr*>(&server_address),
             sizeof(server_address)) == -1)
    {
        std::perror("bind");
        close(server_fd);
        return;
    }

    if (listen(server_fd, SOMAXCONN) == -1)
    {
        std::perror("listen");
        close(server_fd);
        return;
    }

    std::cout << "Listening on port " << m_port << '\n';

    while (true)
    {
        sockaddr_in client_address{};
        socklen_t client_length{sizeof(client_address)};

        int client_fd{accept(server_fd,
                             reinterpret_cast<sockaddr*>(&client_address),
                             &client_length)};

        if (client_fd == -1)
        {
            std::perror("accept");
            continue;
        }

        char buffer[4096]{};

        ssize_t bytes_received{recv(client_fd, buffer, sizeof(buffer) - 1, 0)};

        if (bytes_received <= 0)
        {
            close(client_fd);
            continue;
        }

        buffer[bytes_received] = '\0';

        Request request = parse_request(buffer);

        // Start timing AFTER parsing request
        auto start = std::chrono::high_resolution_clock::now();

        Response response = route(request);
        std::string raw = build_response(response);

        ssize_t sent = send(client_fd, raw.c_str(), raw.size(), 0);
        if (sent == -1)
        {
            std::perror("send");
        }

        // End timing AFTER response is sent
        auto end = std::chrono::high_resolution_clock::now();
        auto duration =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start)
                .count();

        // Logging
        std::string log_line = request.method + " " + request.path + " " +
                               std::to_string(response.status_code) + " " +
                               std::to_string(duration) + "us";

        if (response.status_code >= 400)
        {
            log_error(log_line);
        }
        else
        {
            log_info(log_line);
        }

        close(client_fd);
    }

    close(server_fd);
}
