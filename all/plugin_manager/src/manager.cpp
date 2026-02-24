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
  std::cout << "Plugin manager initialized" << std::endl;
  
  std::ifstream modules_file(modules);
  if(!modules_file.is_open()){
    Logger::log("Not found modules.json ",Logger::TypeLog::FATAL);
    return false;
  }

try{
  json data;
  modules_file >> data;
  
  if(!this->check(data)){
    return false;
  } 
  
  for(const auto& item : data[this->main_key]){
    this->plugins.push_back(Plugin(item));  
  }
  
} catch (json::parse_error& er){
  Logger::log("Parse error: "+std::string(er.what()) ,Logger::TypeLog::FATAL);
  return false; 
} catch (json::out_of_range& er){
  
  return false;
} catch (json::other_error& er) {
  
  return false; 
}


    modules_file.close();
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




