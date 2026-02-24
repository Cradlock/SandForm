#pragma once 




#include <filesystem>
#include <nlohmann/json_fwd.hpp>
#include <string>



class Plugin{
  bool required;
  std::string id; 
  std::filesystem::path path;  
  

public:
  Plugin(const nlohmann::json& obj);


};



