







#include "core/error.h"
#include "core/resources_types/enums.h"
#include "core/services/log.h"
#include "core/services/resources.h"
#include <filesystem>
#include <mutex>


namespace fs = std::filesystem;



RESULT_CODE ResourceManager::load(
    const fs::path& path_p,
    IResource** out,
    ResourceLoadType type_load
){

  if(!out){
    return RESULT_CODE::INVALID_PARAMETR;
  }

  fs::path path = fs::absolute(path_p);
  
  if(check_extension(path) == RESULT_CODE::UNKNOW_EXTENSION){
    return RESULT_CODE::UNKNOW_EXTENSION;
  }
  
  if(get_from_cache(path,out) == RESULT_CODE::SUCCESS){
    return RESULT_CODE::SUCCESS;  
  }

  if(!fs::exists(path)){
    return RESULT_CODE::NOT_FOUND;
  }

    
  IResource* res = get_or_create(path);
  if(!res) {
    return RESULT_CODE::UNKNOW_EXTENSION;
  }
  
  auto state = res->getStatus();
  
  prepare_resource(res,type_load,ResourceTaskType::LOAD);

  *out = res;
  return RESULT_CODE::SUCCESS;
}

RESULT_CODE ResourceManager::create(
    const fs::path& path_p, 
    IResource **out, 
    ResourceLoadType type_load 
){

  if(!out){
    return RESULT_CODE::INVALID_PARAMETR;
  }
  
  fs::path path = fs::absolute(path_p);
  
  if(check_extension(path) == RESULT_CODE::UNKNOW_EXTENSION){
    return RESULT_CODE::UNKNOW_EXTENSION;
  }

  if(get_from_cache(path,out) == RESULT_CODE::SUCCESS){
    return RESULT_CODE::SUCCESS;
  }
  
  IResource* res = get_or_create(path);
    
  prepare_resource(res,type_load,ResourceTaskType::CREATE);

  *out = res;
  return RESULT_CODE::SUCCESS;
}











