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
    std::cout << "Starting server on port " << m_port << '\n';

    int server_fd{socket(AF_INET, SOCK_STREAM, 0)};

    if (server_fd == -1)
    {
        std::cerr << "socket failed: " << std::strerror(errno) << '\n';
        return;
    }

    std::cout << "Socket created successfully\n";

    close(server_fd);
}
