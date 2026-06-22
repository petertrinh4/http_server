# pshell / C++ HTTP Server

A lightweight HTTP/1.1 server written in modern C++ from scratch, built to learn systems programming, networking fundamentals, and backend architecture design.

This project implements a basic web server capable of handling HTTP requests, routing, and serving static files using POSIX sockets.

## Screenshots

![Server Running](screenshots/server.png)

![Browser Request](screenshots/browser.png)

![Curl Response](screenshots/curl.png)

## Features

- Custom TCP server using POSIX sockets (socket, bind, listen, accept)
- HTTP/1.1 request parsing
- Basic routing system (/ , /hello, etc.)
- Static file server (serves HTML, CSS, JS from public directory)
- MIME type detection for common file types
- HTTP response builder with headers
- 404 handling for missing routes and files
- Modular architecture separating server, router, request, response, and file handling logic

## Architecture Overview

The server follows a simple request to response pipeline:

Client Request
→ recv()
→ Request Parser (parse_request)
→ Router (route)
→ Static File Server (if applicable)
→ Response Builder (build_response)
→ send()
→ Client Response

## Project Structure

include/
    request.hpp
    response.hpp
    router.hpp
    server.hpp
    file_server.hpp

src/
    main.cpp
    server.cpp
    request.cpp
    response.cpp
    router.cpp
    file_server.cpp

public/
    index.html
    style.css

CMakeLists.txt

## Build Instructions

Requirements:
- C++17 compiler (g++ or clang++)
- CMake 3.15+

Build:

cmake -S . -B build
cmake --build build

Run:

./build/http_server

Server runs at:
http://localhost:8080

## Testing

Basic requests:

curl http://localhost:8080/
curl http://localhost:8080/hello
curl http://localhost:8080/index.html

Inspect full HTTP response:

curl -i http://localhost:8080/

Test missing route (404):

curl -i http://localhost:8080/doesnotexist

## Example Routes

/           Serves public/index.html
/hello      Returns a simple text response
/style.css  Serves static CSS file
/anything   Returns 404 if not matched

## Implementation Details

Networking:
- Raw POSIX sockets
- Single-threaded blocking I/O model
- One request handled at a time

HTTP Handling:
- Manual parsing of HTTP request line
- Supports GET requests
- Basic header generation (Content-Type, Content-Length)

Static File Server:
- Maps URL paths to public directory
- Loads files using file streams
- Detects MIME types based on file extension

## Limitations

- Single-threaded (no concurrency)
- Only supports HTTP GET requests
- No persistent connections
- No request body parsing
- Minimal error handling

## Purpose

This project was built to understand:
- How HTTP works under the hood
- How web servers handle sockets
- Low-level networking in C++
- Basic backend system design

## Future Improvements

- Multi-threaded request handling
- POST request support
- JSON API endpoints
- Thread pool architecture
- Configurable routing system
- Path traversal protection
- Improved logging system
