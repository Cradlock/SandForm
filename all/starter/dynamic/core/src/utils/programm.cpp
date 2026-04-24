
#include "core/utils/prg.h"
#include <iostream>
#include <filesystem>




#ifdef _WIN32
  #include <windows.h> 
#elif __linux__
  #include <unistd.h>
  #include <limits.h>
#endif


namespace fs = std::filesystem;

fs::path get_programm_root(){
#ifdef _WIN32
  // Windows: Используем WinAPI
    wchar_t buffer[MAX_PATH];
    GetModuleFileNameW(NULL, buffer, MAX_PATH);
    return fs::path(buffer).parent_path();
#elif __linux__
  // Linux: Читаем символическую ссылку в /proc
    char buffer[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", buffer, PATH_MAX);
    if (count != -1) {
        return fs::path(std::string(buffer, count)).parent_path();
    }
#endif
  
    return fs::current_path();
}





