#include "plugin_manager/manager.h"
#include "core/services/log.h"
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json_fwd.hpp>
#include "nlohmann/json.hpp"
#include "plugin_manager/plugin.h"

namespace fs = std::filesystem;


using nlohmann::json;

PluginManager::PluginManager(fs::path modules_file,std::string main_key_p) : 
  modules(modules_file),
  main_key(main_key_p) {

  
}


bool PluginManager::init(){
  
 return true;
}



bool PluginManager::check(const json& obj){
  if(!obj.contains(this->main_key)){
    Logger::log("Key '" + this->main_key + "' not found", Logger::TypeLog::FATAL);
    return false;
  }
    
  auto& modules_node = obj[this->main_key];
  
  if(!modules_node.is_array()){
    Logger::log("'" + this->main_key + "' must be an array!", Logger::TypeLog::FATAL);
    return false;
  }
  
  return true;
}




