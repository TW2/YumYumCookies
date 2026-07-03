#pragma once

#include <string>

namespace FFmpeg {
    bool IsAvailable();
    std::string GetVersion();
    std::string ProbeFile(const std::string& path);
}
