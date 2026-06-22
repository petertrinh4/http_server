cmake_minimum_required(VERSION 3.15)

project(http_server VERSION 1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(
        -Wall
        -Wextra
        -Werror
        -pedantic
    )

    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(
            -fsanitize=address,undefined
            -fno-omit-frame-pointer
            -g
        )

        add_link_options(
            -fsanitize=address,undefined
        )
    endif()
endif()

set(SOURCES
    src/main.cpp
    src/server.cpp
    src/router.cpp
    src/response.cpp
    src/request.cpp
    src/file_server.cpp
    src/logger.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        include
)
