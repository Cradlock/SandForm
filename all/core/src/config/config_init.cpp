#include "core/services/config/Config.h" 
#include "sfr/common/status_codes.h"
#include "core/services/logger/Logger.h"
#include <iostream>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>

namespace fs = std::filesystem;


fs::path Config::root;

fs::path Config::settings_dir_path = "settings/";
std::unordered_map<
std::string,std::unique_ptr<ConfigObject>
> Config::storage = {};


void Config::init(
  const fs::path& root_p
){
  root = root_p;
  settings_dir_path = root;

  if(!fs::exists(settings_dir_path)){
    fs::create_directories(settings_dir_path);
  }
   
  for(auto iter : fs::directory_iterator(settings_dir_path)){
    if(!iter.is_directory()){
      std::string ext = iter.path().extension().string();
      if(ext == ".json"){
      
      }
    }
  }

}

void Config::shutdown(){
  
  storage.clear();
}







ConfigObject::~ConfigObject(){
  
}


