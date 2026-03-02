#include "core/resources_types/json.h"
#include "core/services/log.h"
#include "core/services/resources.h"
#include <exception>
#include <filesystem>
#include <fstream>
#include <functional>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string>



namespace fs = std::filesystem;


JsonResource::~JsonResource(){

}



void JsonResource::load(){
  state.store(ResourceState::RES_STATE_LOADING);
  
  if(!fs::exists(path)){ 
    state.store(ResourceState::RES_STATE_ERROR_NOT_FOUND);
    return;
  }

  try{
    std::ifstream file(path);
    
    if(!file.is_open()){
      state.store(ResourceState::RES_StATE_OS_ERROR);
      return;
    }
    
    file >> this->data;
  }catch(const nlohmann::json::parse_error& er){
    Logger::log("JSON Parse Error: " + std::string(er.what()), Logger::TypeLog::WARNING);
    state.store(ResourceState::RES_STATE_ERROR_FORMAT);
  }catch(const std::exception& er){
    Logger::log("Generic Error in JsonResource: " + std::string(er.what()) ,Logger::TypeLog::WARNING);
    state.store(ResourceState::RES_STATE_ERROR_INTERNAL);
  }
}



void JsonResource::registry(){
  ResourceManager::register_creator(".json", [](const std::filesystem::path& p) {
    return new JsonResource(p, ".json"); 
  });
}





