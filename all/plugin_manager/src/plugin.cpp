#include "plugin_manager/plugin.h"

#include "core/resources_types/json.h"
#include "nlohmann/json.hpp"
#include <filesystem>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <iostream>

namespace fs = std::filesystem;
using nlohmann::json;


Plugin::Plugin(const JsonResource* obj){
  std::string id;
  std::filesystem::path path; 
  bool required;
  

  this->id = id;
  this->path = path;
  this->required = required;

}



