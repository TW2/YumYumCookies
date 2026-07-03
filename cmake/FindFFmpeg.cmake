# FindFFmpeg.cmake - Locate FFmpeg libraries for cross-platform builds.
# Supports pkg-config on Unix and manual search via FFMPEG_DIR/FFMPEG_ROOT.

find_package(PkgConfig QUIET)

set(FFMPEG_FOUND FALSE)
set(FFMPEG_INCLUDE_DIRS)
set(FFMPEG_LIBRARIES)
set(FFMPEG_VERSION)

if(PKG_CONFIG_FOUND)
    pkg_check_modules(FFMPEG_AVFORMAT QUIET libavformat)
    pkg_check_modules(FFMPEG_AVCODEC QUIET libavcodec)
    pkg_check_modules(FFMPEG_AVUTIL QUIET libavutil)

    if(FFMPEG_AVFORMAT_FOUND AND FFMPEG_AVCODEC_FOUND AND FFMPEG_AVUTIL_FOUND)
        set(FFMPEG_FOUND TRUE)
        list(APPEND FFMPEG_INCLUDE_DIRS
            ${FFMPEG_AVFORMAT_INCLUDE_DIRS}
            ${FFMPEG_AVCODEC_INCLUDE_DIRS}
            ${FFMPEG_AVUTIL_INCLUDE_DIRS}
        )
        list(REMOVE_DUPLICATES FFMPEG_INCLUDE_DIRS)

        list(APPEND FFMPEG_LIBRARIES
            ${FFMPEG_AVFORMAT_LIBRARIES}
            ${FFMPEG_AVCODEC_LIBRARIES}
            ${FFMPEG_AVUTIL_LIBRARIES}
            ${FFMPEG_AVFORMAT_LDFLAGS_OTHER}
            ${FFMPEG_AVCODEC_LDFLAGS_OTHER}
            ${FFMPEG_AVUTIL_LDFLAGS_OTHER}
        )
        list(REMOVE_DUPLICATES FFMPEG_LIBRARIES)

        set(FFMPEG_VERSION ${FFMPEG_AVFORMAT_VERSION})
    endif()
endif()

if(NOT FFMPEG_FOUND)
    find_path(FFMPEG_INCLUDE_DIR
        NAMES libavformat/avformat.h
        PATHS
            ENV FFMPEG_DIR
            ENV FFMPEG_ROOT
            "/usr/local"
            "/usr"
            "C:/ffmpeg"
            "C:/Program Files/ffmpeg"
            "C:/Program Files (x86)/ffmpeg"
        PATH_SUFFIXES include include/ffmpeg include/lib
    )

    find_library(FFMPEG_AVFORMAT_LIBRARY
        NAMES avformat libavformat
        PATHS
            ENV FFMPEG_DIR
            ENV FFMPEG_ROOT
            "/usr/local/lib"
            "/usr/lib"
            "C:/ffmpeg/lib"
            "C:/Program Files/ffmpeg/lib"
            "C:/Program Files (x86)/ffmpeg/lib"
        PATH_SUFFIXES lib lib64 lib/x64 lib/x86
    )

    find_library(FFMPEG_AVCODEC_LIBRARY
        NAMES avcodec libavcodec
        PATHS
            ENV FFMPEG_DIR
            ENV FFMPEG_ROOT
            "/usr/local/lib"
            "/usr/lib"
            "C:/ffmpeg/lib"
            "C:/Program Files/ffmpeg/lib"
            "C:/Program Files (x86)/ffmpeg/lib"
        PATH_SUFFIXES lib lib64 lib/x64 lib/x86
    )

    find_library(FFMPEG_AVUTIL_LIBRARY
        NAMES avutil libavutil
        PATHS
            ENV FFMPEG_DIR
            ENV FFMPEG_ROOT
            "/usr/local/lib"
            "/usr/lib"
            "C:/ffmpeg/lib"
            "C:/Program Files/ffmpeg/lib"
            "C:/Program Files (x86)/ffmpeg/lib"
        PATH_SUFFIXES lib lib64 lib/x64 lib/x86
    )

    if(FFMPEG_INCLUDE_DIR AND FFMPEG_AVFORMAT_LIBRARY AND FFMPEG_AVCODEC_LIBRARY AND FFMPEG_AVUTIL_LIBRARY)
        set(FFMPEG_FOUND TRUE)
        set(FFMPEG_INCLUDE_DIRS ${FFMPEG_INCLUDE_DIR})
        set(FFMPEG_LIBRARIES ${FFMPEG_AVFORMAT_LIBRARY} ${FFMPEG_AVCODEC_LIBRARY} ${FFMPEG_AVUTIL_LIBRARY})
    endif()
endif()

if(FFMPEG_FOUND)
    add_library(FFmpeg::FFmpeg INTERFACE IMPORTED)
    target_include_directories(FFmpeg::FFmpeg INTERFACE ${FFMPEG_INCLUDE_DIRS})
    target_link_libraries(FFmpeg::FFmpeg INTERFACE ${FFMPEG_LIBRARIES})
endif()

set(FFMPEG_FOUND ${FFMPEG_FOUND} CACHE BOOL "Found FFmpeg libraries")
mark_as_advanced(FFMPEG_INCLUDE_DIR FFMPEG_AVFORMAT_LIBRARY FFMPEG_AVCODEC_LIBRARY FFMPEG_AVUTIL_LIBRARY)
