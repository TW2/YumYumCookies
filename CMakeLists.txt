cmake_minimum_required(VERSION 3.16)
project(YYCookies LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(wxWidgets REQUIRED COMPONENTS core base)
find_package(Threads REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(YYCookies main.cpp)
target_link_libraries(YYCookies PRIVATE ${wxWidgets_LIBRARIES} Threads::Threads)
target_compile_options(YYCookies PRIVATE -pthread)
target_link_options(YYCookies PRIVATE -pthread)

add_custom_target(run-YYCookies
    COMMAND ${CMAKE_COMMAND} -E env LD_PRELOAD=/usr/lib/x86_64-linux-gnu/libpthread.so.0 $<TARGET_FILE:YYCookies>
    USES_TERMINAL
)
