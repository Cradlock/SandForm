#include "plugin_manager/plugin.h"

#include "nlohmann/json.hpp"
#include <filesystem>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <iostream>

namespace fs = std::filesystem;
using nlohmann::json;


Plugin::Plugin(const json& obj){
  std::string id;
  std::filesystem::path path; 
  bool required;
  
  try{
    id = obj.at("id").get<std::string>();
    path = fs::path(obj.at("path").get<std::string>()); 
    
  } catch (const json::out_of_range& e){
  
  }
  
  required = obj.value("required",false);
  
  this->id = id;
  this->path = path;
  this->required = required;

}



