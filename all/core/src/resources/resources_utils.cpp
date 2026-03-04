






#include "core/error.h"
#include "core/services/log.h"
#include "core/services/resources.h"
#include <string_view>



namespace fs = std::filesystem;

RESULT_CODE ResourceManager::get_from_cache(
  const fs::path& path, 
  IResource **out
){
  std::lock_guard<std::mutex> lock(mtx);
  auto it = storage.find(fs::absolute(path));
  if(it != storage.end()){
    *out = it->second;
    (*out)->ref_count++;
    return RESULT_CODE::SUCCESS;
  }
  
  return RESULT_CODE::NOT_FOUND;
}





RESULT_CODE ResourceManager::check_extension(
  const fs::path& path
){
  std::string ext = path.extension().string();
  auto it = creators.find(ext);
  if(it == creators.end()){
    Logger::log("unknow extension: " + ext + " at " + path.filename().string(),TypeLog::PE_WARNING);
    return RESULT_CODE::UNKNOW_EXTENSION;
  }
  return RESULT_CODE::SUCCESS;

}



void ResourceManager::register_creator(
  std::string ext, 
  ResourceCreator func
){
  creators[ext] = func;
}









