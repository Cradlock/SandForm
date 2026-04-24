#include "core/services/resources/in/manager.h"
#include "sfr/common/status_codes.h"
#include "sfr/core/resources/Interface.h"
#include "sfr/core/resources/results.h"
#include "sfr/core/resources/states.h"
#include "core/services/logger/Logger.h"
#include "core/services/resources/Resources.h"



using RES_STREAM = std::pair<RESULT_CODE,std::unique_ptr<IStream>>;

ResResource ResourceManager::load(
    const std::string_view uri, 
    ResourceActionType tp
){
  ResResource res = {
    RESULT_CODE::SUCCESS,
    nullptr 
  }; 

  
  RES_STREAM stream_sh = ResourceManager::GetStream(uri, ResourceTaskType::LOAD);
  if(stream_sh.first != RESULT_CODE::SUCCESS){
    res.code = stream_sh.first;
    return res;
  }

  if(tp == ResourceActionType::SYNC){
    
  } 

  return res;
}



















