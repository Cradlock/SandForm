#include "core/services/config.h" 
#include "core/error.h"
#include "core/resources_types/json.h"
#include "core/services/log.h"
#include "core/services/resources.h"
#include "core/utils.h"
#include <iostream>
#include <filesystem>
#include <string>
#include <unordered_map>

namespace fs = std::filesystem;


fs::path Config::root;

fs::path Config::settings_dir_path = "settings/";
std::unordered_map<
std::string, ConfigObject
> Config::storage = {};


void Config::init(
  const fs::path& root_p
){
  root = root_p;
  settings_dir_path = root / settings_dir_path;

  if(!fs::exists(settings_dir_path)){
    fs::create_directories(settings_dir_path);
  }
   
  for(auto iter : fs::directory_iterator(settings_dir_path)){
    if(!iter.is_directory()){
      std::string name = iter.path().filename().string();
      IResource* file = nullptr;
      RESULT_CODE status = ResourceManager::wait_create(iter.path(), &file);
      if(status == RESULT_CODE::SUCCESS && file){
        JsonResource* data_file = static_cast<JsonResource*>(file);
        ConfigObject cfg(name,data_file);

      } else {
        Logger::log("Not load config file:"+name+" with status code:"+ std::to_string(status),TypeLog::PE_WARNING);
      }
    }
  }

}

void Config::shutdown(){

}


RESULT_CODE Config::getConfig(
  std::string name, 
  ConfigObject **out
){
// Проверка на аргументы 
  if(!out) return RESULT_CODE::INVALID_PARAMETR;

// Существование конфига в памяти
  auto it = storage.find(name);
  if(it == storage.end()){
    // Если нет новый конфиг
    return CREATED_NEW;
  }
// Если есть отдаем его
  *out = &it->second;
  return SUCCESS;
}





ConfigObject::ConfigObject(std::string p,JsonResource* file_p) :
  name(p),file(file_p)
{
 
}



