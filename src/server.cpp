#include "server.hpp"
#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

Server::Server(int port) : m_port{port} {}

void Server::start()
{
    std::cout << "Starting server on port " << m_port << '\n'; // socket()

    int server_fd{socket(AF_INET, SOCK_STREAM, 0)};

    if (server_fd == -1)
    {
        std::cerr << "socket failed: " << std::strerror(errno) << '\n';
        return;
    }

    std::cout << "Socket created successfully\n";

    sockaddr_in server_address{}; // bind()

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

    std::cout << "Socket bound to port " << m_port << '\n';

    if (listen(server_fd, SOMAXCONN) == -1) // listen()
    {
        std::perror("listen");
        close(server_fd);
        return;
    }

    std::cout << "Listening for connections on port " << m_port << '\n';

    std::cout << "Waiting for a client...\n";

    sockaddr_in client_address{};
    socklen_t client_length{sizeof(client_address)};

    int client_fd{accept(server_fd,
                         reinterpret_cast<sockaddr*>(&client_address),
                         &client_length)};

    if (client_fd == -1)
    {
        std::perror("accept");
        close(server_fd);
        return;
    }

    std::cout << "Client connected!\n";

    char buffer[4096]{}; // recv()

    ssize_t bytes_received{recv(client_fd, buffer, sizeof(buffer) - 1, 0)};

    if (bytes_received < 0)
    {
        std::perror("recv");
        close(client_fd);
        close(server_fd);
        return;
    }

    buffer[bytes_received] = '\0';

    std::cout << "Received request:\n"; // send()
    std::cout << buffer << '\n';

    const char* response{"HTTP/1.1 200 OK\r\n"
                         "Content-Type: text/plain\r\n"
                         "\r\n"
                         "Hello World\n"};

    ssize_t bytes_sent{send(client_fd, response, std::strlen(response), 0)};

    if (bytes_sent < 0)
    {
        std::perror("send");
    }

    close(server_fd);
}
