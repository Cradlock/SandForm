
#include "core/services/resources.h"











void ResourceManager::resource_worker(){
  
  while(true){
    Task task;

    {
      std::unique_lock<std::mutex> lock(mtx_tasks);

      resource_cv.wait(lock,[] {
        return !tasks.empty() || !should_run;
      });
      
      if(!should_run && tasks.empty() ){
        break;
      }
      
      task = tasks.front();
      tasks.pop();
    }
    
    action(task);

  }
  
}


