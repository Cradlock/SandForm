






#include "core/error.h"
#include "core/resources_types/enums.h"
#include "core/services/log.h"
#include "core/services/resources.h"
#include <filesystem>
#include <mutex>
#include <string_view>



namespace fs = std::filesystem;

RESULT_CODE ResourceManager::get_from_cache(
  const fs::path& path, 
  IResource **out
){
  std::lock_guard<std::mutex> lock(mtx_storage);
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



IResource* ResourceManager::get_or_create(
  const fs::path& path
){
  
  std::unique_lock<std::mutex> lock(mtx_storage);

  auto it = storage.find(path);
  if(it != storage.end()){
    return it->second;
  }

  std::string ext = path.extension().string();
  auto creator_it = creators.find(ext);
  if (creator_it == creators.end()) return nullptr;

  IResource* res = creator_it->second(path);
  storage[path] = res;
  return res;
}


void ResourceManager::wait_for_resource(IResource* res) {
    while (res->getStatus() < ResourceState::RES_STATE_SUCCESS) {
        std::this_thread::yield();
    }
}

void ResourceManager::push_task(Task task) {
    {
        std::unique_lock<std::mutex> lock(mtx_tasks);
        tasks.push(task);
    }
    resource_cv.notify_one();
}

RESULT_CODE ResourceManager::action(Task task){

  IResource* data = task.getData();
  switch (task.getType()) {
    case ResourceTaskType::CREATE:
      data->create();
      break; 
    
    case ResourceTaskType::LOAD:
      data->load();
      break;

    case ResourceTaskType::RELEASE:
      delete data;
      break;

    case ResourceTaskType::DESTROY:
      data->destroy();
      break;
    
    case ResourceTaskType::SAVE:
      break;

    default:
      return RESULT_CODE::UNKNOW_ACTION;
  }   
  
  return RESULT_CODE::SUCCESS;
}

void ResourceManager::prepare_resource(
  IResource* res,
  ResourceLoadType type_load, 
  ResourceTaskType type_task
){
  auto state = res->getStatus();
  Task task(type_task,res);
  
  if(type_load == ResourceLoadType::SYNC){
    if(state == ResourceState::RES_STATE_EMPTY){
      action(task);
    }else{
      wait_for_resource(res);
    }
  }else{
    res->state.store(ResourceState::RES_STATE_IN_QUEUE);
    push_task(task);
  }


}


