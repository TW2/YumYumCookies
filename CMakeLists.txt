cmake_minimum_required(VERSION 3.16)
project(YYCookies LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
find_package(FFmpeg QUIET)
find_package(wxWidgets REQUIRED COMPONENTS core base)
find_package(Threads REQUIRED)
include(${wxWidgets_USE_FILE})

set(YYCOOKIES_SOURCES main.cpp ffmpeg_helper.cpp)

add_executable(YYCookies ${YYCOOKIES_SOURCES})
target_link_libraries(YYCookies PRIVATE ${wxWidgets_LIBRARIES} Threads::Threads)
if(FFMPEG_FOUND)
    target_link_libraries(YYCookies PRIVATE FFmpeg::FFmpeg)
    target_compile_definitions(YYCookies PRIVATE YYCOOKIES_USE_FFMPEG=1)
else()
    # If the provided FindFFmpeg module didn't produce a usable target,
    # try pkg-config as a fallback and create an imported target so linking
    # behaves like the Find module.
    find_package(PkgConfig QUIET)
    if(PKG_CONFIG_FOUND)
        pkg_check_modules(PC_FFMPEG QUIET libavformat libavcodec libavutil)
        if(PC_FFMPEG_FOUND)
            add_library(FFmpeg::FFmpeg INTERFACE IMPORTED)
            target_include_directories(FFmpeg::FFmpeg INTERFACE ${PC_FFMPEG_INCLUDE_DIRS})
            target_link_libraries(FFmpeg::FFmpeg INTERFACE ${PC_FFMPEG_LIBRARIES})
            target_link_libraries(YYCookies PRIVATE FFmpeg::FFmpeg)
            target_compile_definitions(YYCookies PRIVATE YYCOOKIES_USE_FFMPEG=1)
        else()
            target_compile_definitions(YYCookies PRIVATE YYCOOKIES_USE_FFMPEG=0)
        endif()
    else()
        target_compile_definitions(YYCookies PRIVATE YYCOOKIES_USE_FFMPEG=0)
    endif()
endif()

target_compile_definitions(YYCookies PRIVATE YYCOOKIES_TARGET_LINUX=1)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_options(YYCookies PRIVATE -pthread)
    target_link_options(YYCookies PRIVATE -pthread)
elseif(WIN32)
    add_executable(YYCookies-windows ${YYCOOKIES_SOURCES})
    target_link_libraries(YYCookies-windows PRIVATE ${wxWidgets_LIBRARIES} Threads::Threads)
    if(FFMPEG_FOUND)
        target_link_libraries(YYCookies-windows PRIVATE FFmpeg::FFmpeg)
        target_compile_definitions(YYCookies-windows PRIVATE YYCOOKIES_USE_FFMPEG=1)
    else()
        target_compile_definitions(YYCookies-windows PRIVATE YYCOOKIES_USE_FFMPEG=0)
    endif()
    target_compile_definitions(YYCookies-windows PRIVATE YYCOOKIES_TARGET_WINDOWS=1)
elseif(APPLE)
    add_executable(YYCookies-macos ${YYCOOKIES_SOURCES})
    target_link_libraries(YYCookies-macos PRIVATE ${wxWidgets_LIBRARIES} Threads::Threads)
    if(FFMPEG_FOUND)
        target_link_libraries(YYCookies-macos PRIVATE FFmpeg::FFmpeg)
        target_compile_definitions(YYCookies-macos PRIVATE YYCOOKIES_USE_FFMPEG=1)
    else()
        target_compile_definitions(YYCookies-macos PRIVATE YYCOOKIES_USE_FFMPEG=0)
    endif()
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

