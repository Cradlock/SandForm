







#include "core/error.h"
#include "core/services/log.h"
#include "core/services/resources.h"
#include <filesystem>


namespace fs = std::filesystem;



RESULT_CODE ResourceManager::load(
    const fs::path& path_p,
    IResource** out,
    ResourceLoadType type_load
){
  fs::path path = fs::absolute(path_p);

  if(!out){
    return RESULT_CODE::INVALID_PARAMETR;
  }

  if(check_extension(path) == RESULT_CODE::UNKNOW_EXTENSION){
    return RESULT_CODE::UNKNOW_EXTENSION;
  }
  
  if(get_from_cache(path,out) == RESULT_CODE::SUCCESS){
    return RESULT_CODE::SUCCESS;  
  }

  if(!fs::exists(path)){
    return RESULT_CODE::NOT_FOUND;
  }

  
  std::string ext = path.extension().string();  
  ResourceCreator creator = creators[ext];
  IResource* res = creator(path);
  
  res->state.store(ResourceState::RES_STATE_IN_QUEUE);
 

  switch (type_load) {
    case ResourceLoadType::ASYNC:
      

      break;

    case ResourceLoadType::SYNC:


      break;

    default:
      return RESULT_CODE::INVALID_PARAMETR;
      break;
  }

  *out = res;
  return RESULT_CODE::SUCCESS;
}






RESULT_CODE ResourceManager::create(
    const fs::path& path_p, 
    IResource **out, 
    ResourceLoadType tp
){

  if(!out){
    return RESULT_CODE::INVALID_PARAMETR;
  }
  
  fs::path path = fs::absolute(path_p);

  if(get_from_cache(path,out) == RESULT_CODE::SUCCESS){
    return RESULT_CODE::SUCCESS;
  }
  

}











