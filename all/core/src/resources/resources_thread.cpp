











#include "core/services/resources.h"
void ResourceManager::resource_worker(){
  
  while(true){
    Task* task = nullptr;

    {
      std::unique_lock<std::mutex> lock(mtx);

      resource_cv.wait(lock,[] {
        return !tasks.empty() || !should_run;
      });
      
      if(!should_run && tasks.empty() ){
        break;
      }

    }



  }
  
}


