#include "core/services/config.h" 
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;


fs::path Config::settings_dir_path = "/settings";



void Config::init(){
  if(!fs::exists(settings_dir_path)){
    fs::create_directories(settings_dir_path);
  }


}






void Config::shutdown(){

}
