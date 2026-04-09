#pragma once


#include "core/error.h"
#include "core/resources_types/json.h"
#include "plugin_manager/plugin.h"
#include <filesystem>
#include <string>
#include <vector>

class PluginManager{
  
  std::string modules_filename;
  std::filesystem::path root; 

  std::vector<Plugin> plugins;
  
  std::string main_key;

public:
  PluginManager(const std::string&,std::string main_key);
  
  RESULT_CODE init(
    const std::filesystem::path&
  );
  
  RESULT_CODE load_modules(
    const JsonResource*
  );
};
