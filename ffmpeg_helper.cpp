#include "ffmpeg_helper.h"
#include <sstream>

#ifdef __has_include
#  if __has_include(<libavformat/avformat.h>)
#    ifdef __cplusplus
extern "C" {
#    endif
#    include <libavformat/avformat.h>
#    include <libavcodec/avcodec.h>
#    include <libavutil/avutil.h>
#    ifdef __cplusplus
}
#    endif
#    define FFMPEG_HEADERS_AVAILABLE 1
#  endif
#endif

#ifndef FFMPEG_HEADERS_AVAILABLE
#  define FFMPEG_HEADERS_AVAILABLE 0
#endif

namespace FFmpeg {

bool IsAvailable() {
#if defined(YYCOOKIES_USE_FFMPEG) && YYCOOKIES_USE_FFMPEG
    return true;
#else
    return false;
#endif
}

std::string GetVersion() {
#if defined(YYCOOKIES_USE_FFMPEG) && YYCOOKIES_USE_FFMPEG
    const char* version = av_version_info();
    return version ? std::string(version) : std::string("unknown");
#else
    return "unavailable";
#endif
}

std::string ProbeFile(const std::string& path) {
#if defined(YYCOOKIES_USE_FFMPEG) && YYCOOKIES_USE_FFMPEG
    AVFormatContext* ctx = nullptr;
    if (avformat_open_input(&ctx, path.c_str(), nullptr, nullptr) != 0) {
        return "failed to open file";
    }
    avformat_find_stream_info(ctx, nullptr);
    std::ostringstream info;
    info << "format=" << (ctx->iformat ? ctx->iformat->name : "unknown") << "; streams=" << ctx->nb_streams;
    avformat_close_input(&ctx);
    return info.str();
#else
    return "unavailable";
#endif
}

} // namespace FFmpeg
