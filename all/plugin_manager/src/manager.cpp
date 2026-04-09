#include "plugin_manager/manager.h"
#include "core/error.h"
#include "core/resources_types/json.h"
#include "core/services/log.h"
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json_fwd.hpp>
#include "core/services/resources.h"
#include "core/types.h"
#include "nlohmann/json.hpp"
#include "plugin_manager/plugin.h"

namespace fs = std::filesystem;


using nlohmann::json;

PluginManager::PluginManager(
  const std::string& modules_filename,
  std::string main_key_p
) : 
  modules_filename(modules_filename),
  main_key(main_key_p) {

  
}


RESULT_CODE PluginManager::init(
  const std::filesystem::path& root_directory
){
  
  IResource* base_res = nullptr;
  std::filesystem::path path = root_directory / this->modules_filename;
  RESULT_CODE code = ResourceManager::load(
      path,
      &base_res, 
      ResourceLoadType::SYNC
  );
  
  if(code != RESULT_CODE::SUCCESS){
    return code;
  }
  JsonResource* json_res = static_cast<JsonResource*>(base_res);
  
  return RESULT_CODE::SUCCESS;
}



RESULT_CODE PluginManager::load_modules(
  const JsonResource* res
){
  size_t length = 0;
  
  for(int i = 0;i < length;++i){
     
  }

  return RESULT_CODE::SUCCESS;
}




