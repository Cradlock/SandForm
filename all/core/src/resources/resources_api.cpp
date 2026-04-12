#include "sfr/common/status_codes.h"
#include "sfr/core/resources/states.h"
#include "core/services/logger/Logger.h"
#include "core/services/resources/Resources.h"
#include <filesystem>
#include <iostream>
#include <mutex>


namespace fs = std::filesystem;



RESULT_CODE ResourceManager::load(
    const fs::path& path_p,
    Resource** out,
    ResourceLoadType type_load
){
 
  return RESULT_CODE::SUCCESS;
}

RESULT_CODE ResourceManager::create(
    const fs::path& path_p, 
    Resource **out, 
    ResourceLoadType type_load 
){

 

  return RESULT_CODE::SUCCESS;
}


RESULT_CODE ResourceManager::save(
    Resource* in,
    ResourceLoadType tp
){
 

  return RESULT_CODE::SUCCESS;
}
 









