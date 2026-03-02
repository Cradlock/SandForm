#pragma once 

#include "core/services/resources.h"
#include <string>
#include <string_view>


std::string get_current_time();



template<typename CreatorFunc,typename... Args>
void register_formats(CreatorFunc creator,Args... extensions){
  (ResourceManager::register_creator(extensions, creator), ...);
}
