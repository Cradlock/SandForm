#include "core/services/config.h" 
#include "core/error.h"
#include "core/resources_types/json.h"
#include "core/services/log.h"
#include "core/services/resources.h"
#include "core/types.h"
#include "core/utils.h"
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
        
        std::string name = iter.path().stem().filename().string();
        IResource* base_res = nullptr;
        RESULT_CODE code = ResourceManager::load(iter.path(),&base_res, ResourceLoadType::SYNC);
        if(code != RESULT_CODE::SUCCESS){
          Logger::log(
              "Error in get config "+name+" with status code "+std::to_string(code),
              TypeLog::PE_ERROR
          ); 
          continue;
        }

        JsonResource* json_file = static_cast<JsonResource*>(base_res);
        storage[name] = std::make_unique<ConfigObject>(name,json_file);
        
      }
    }
  }

}

void Config::shutdown(){
  
  storage.clear();
}






ConfigObject::ConfigObject(std::string p,JsonResource* file_p) :
  name(p),file(file_p)
{
 
}


ConfigObject::~ConfigObject(){
  
}


