#include "plugin_manager/manager.h"
#include <sfr/common/status_codes.h>
#include "core/services/logger/Logger.h"
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sfr/common/types.h>
#include "plugin_manager/plugin.h"

namespace fs = std::filesystem;



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
   return RESULT_CODE::SUCCESS;
}



RESULT_CODE PluginManager::load_modules(
){
   return RESULT_CODE::SUCCESS;
}




