#include "core/utils.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <chrono>


std::string get_current_time() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm buf{}; // Локальный буфер в стеке

#if defined(_WIN32)
    localtime_s(&buf, &in_time_t); // Безопасно в Windows
#else
    localtime_r(&in_time_t, &buf); // Безопасно в Linux
#endif

    std::stringstream ss;
    ss << std::put_time(&buf, "%Y-%m-%d %X");
    return ss.str();
}
