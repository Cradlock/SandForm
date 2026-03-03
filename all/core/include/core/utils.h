#pragma once 

#include "core/services/resources.h"
#include <filesystem>
#include <string>
#include <string_view>


std::string get_current_time();

void test_1();

template<typename CreatorFunc,typename... Args>
void register_formats(CreatorFunc creator,Args... extensions){
  (ResourceManager::register_creator(extensions, creator), ...);
}


std::filesystem::path get_programm_root();



