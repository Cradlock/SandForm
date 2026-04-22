






#include "core/services/resources/in/manager.h"
#include "sfr/common/status_codes.h"
#include "sfr/core/resources/states.h"
#include "core/services/logger/Logger.h"
#include "core/services/resources/Resources.h"
#include <filesystem>
#include <iostream>
#include <mutex>
#include <string_view>
#include <utility>




using RES_STREAM = std::pair<RESULT_CODE,std::unique_ptr<IStream>>;

RES_STREAM ResourceManager::GetStream(
std::string_view uri,ResourceTaskType task_type
){
  RES_STREAM res = {
    RESULT_CODE::NOT_FOUND,nullptr
  };
  
  for (const auto& pr : ResourceManager::providers) {
    if(pr->canHandle(uri)){
      auto stream = pr->OpenStream(uri,task_type);
      res.first = RESULT_CODE::SUCCESS;
      break;
    } 
  }

  return res;
}


RESULT_CODE ResourceManager::action(Task task){
  
  ResourceTaskType task_type = task.getType();
  std::string_view res_type = task.getData()->getResourceType(); 

  switch (task_type) {
    case LOAD:
       
    case CREATE:
      
    case SAVE:

    case RELEASE:

    default:

      return RESULT_CODE::UNKNOW_ACTION;
      break;
  }


  return RESULT_CODE::SUCCESS;
}





