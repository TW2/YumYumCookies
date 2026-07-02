cmake_minimum_required(VERSION 3.16)
project(YYCookies LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(wxWidgets REQUIRED COMPONENTS core base)
find_package(Threads REQUIRED)
include(${wxWidgets_USE_FILE})

set(YYCOOKIES_SOURCES main.cpp)

add_executable(YYCookies ${YYCOOKIES_SOURCES})
target_link_libraries(YYCookies PRIVATE ${wxWidgets_LIBRARIES} Threads::Threads)

target_compile_definitions(YYCookies PRIVATE YYCOOKIES_TARGET_LINUX=1)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_options(YYCookies PRIVATE -pthread)
    target_link_options(YYCookies PRIVATE -pthread)
elseif(WIN32)
    add_executable(YYCookies-windows ${YYCOOKIES_SOURCES})
    target_link_libraries(YYCookies-windows PRIVATE ${wxWidgets_LIBRARIES} Threads::Threads)
    target_compile_definitions(YYCookies-windows PRIVATE YYCOOKIES_TARGET_WINDOWS=1)
elseif(APPLE)
    add_executable(YYCookies-macos ${YYCOOKIES_SOURCES})
    target_link_libraries(YYCookies-macos PRIVATE ${wxWidgets_LIBRARIES} Threads::Threads)
    target_compile_definitions(YYCookies-macos PRIVATE YYCOOKIES_TARGET_MACOS=1)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_custom_target(run-YYCookies
        COMMAND ${CMAKE_COMMAND} -E env LD_PRELOAD=/usr/lib/x86_64-linux-gnu/libpthread.so.0 $<TARGET_FILE:YYCookies>
        USES_TERMINAL
    )
elseif(WIN32)
    add_custom_target(run-YYCookies
        COMMAND $<TARGET_FILE:YYCookies-windows>
        USES_TERMINAL
    )
elseif(APPLE)
    add_custom_target(run-YYCookies
        COMMAND $<TARGET_FILE:YYCookies-macos>
        USES_TERMINAL
    )
endif()
