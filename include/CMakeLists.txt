cmake_minimum_required(VERSION 3.14)
project(MD5_Crack_API LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenSSL REQUIRED)

# DÉSACTIVE BOOST (cause du bug)
set(CROW_USE_BOOST OFF CACHE BOOL "Disable Boost" FORCE)
set(CROW_ENABLE_SSL OFF)
set(CROW_ENABLE_COMPRESSION OFF)
set(CROW_BUILD_EXAMPLES OFF)
set(CROW_BUILD_TESTS OFF)

include(FetchContent)
FetchContent_Declare(
    crow
    GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
    GIT_TAG v1.0+5
)
FetchContent_MakeAvailable(crow)

FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)

add_executable(md5_api main.cpp Cracker.cpp)

target_link_libraries(md5_api
    OpenSSL::SSL
    OpenSSL::Crypto
    pthread
    Crow::Crow
    nlohmann_json::nlohmann_json
)

target_include_directories(md5_api PRIVATE ${CMAKE_SOURCE_DIR})