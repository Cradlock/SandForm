#pragma once 




#include "core/resources_types/json.h"
#include <filesystem>
#include <string>

#include <nlohmann/json.hpp>

class Plugin{
  bool required;
  std::string id; 
  std::filesystem::path path;  
  

public:

  Plugin(const JsonResource* resource);

};



