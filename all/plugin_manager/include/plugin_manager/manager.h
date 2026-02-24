#pragma once


#include "plugin_manager/plugin.h"
#include <filesystem>
#include <string>
#include <vector>

class PluginManager{
  
  std::filesystem::path modules;

  std::vector<Plugin> plugins;
  
  std::string main_key;

public:
  PluginManager(std::filesystem::path p,std::string main_key);
  
  bool init();
  
  bool check(const nlohmann::json& obj);
};
