






#include "sfr/common/status_codes.h"
#include "sfr/core/resources/states.h"
#include "core/services/logger/Logger.h"
#include "core/services/resources/Resources.h"
#include <filesystem>
#include <iostream>
#include <mutex>
#include <string_view>



namespace fs = std::filesystem;

RESULT_CODE ResourceManager::get_from_cache(
  const fs::path& path, 
  Resource **out
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

  Resource* res = creator_it->second(path);
  storage[path] = res;
  return res;
}


void ResourceManager::wait_for_resource(Resource* res) {
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

  Resource* data = task.getData();
  switch (task.getType()) {
   
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
      data->save();
      break;

    default:
      return RESULT_CODE::UNKNOW_ACTION;
  }   
  
  return RESULT_CODE::SUCCESS;
}


void ResourceManager::prepare_resource(
  Resource* res,
  ResourceLoadType type_load, 
  ResourceTaskType type_task
){
  auto state = res->getStatus();
  Task task(type_task, res);

  // Сценарий 1: Синхронное выполнение
  if(type_load == ResourceLoadType::SYNC) {
    
    switch (type_task) {
      case ResourceTaskType::LOAD:
        // Загружаем только если ресурс еще не трогали
        if(state == ResourceState::RES_STATE_EMPTY) {
          action(task);
        } else {
          wait_for_resource(res);
        }
        break;

      case ResourceTaskType::SAVE:
        // Сохранять можно только то, что уже успешно загружено или создано
        if(state >= ResourceState::RES_STATE_SUCCESS) {
          action(task);
        } else {
          // Если ресурс еще грузится в другом потоке — ждем и потом сохраняем
          wait_for_resource(res);
          action(task);
        }
        break;

      case ResourceTaskType::RELEASE:
      case ResourceTaskType::DESTROY:
        // Перед удалением обязательно ждем завершения всех операций
        wait_for_resource(res);
        action(task);
        break;

      default:
        action(task);
        break;
    }

  } 
  // Сценарий 2: Асинхронное выполнение
  else {
    // Для загрузки ставим статус "в очереди", чтобы другие потоки знали об этом
    if (type_task == ResourceTaskType::LOAD) {
      res->state.store(ResourceState::RES_STATE_IN_QUEUE);
    }
    // Для SAVE статус менять не обязательно, чтобы не сломать чтение из ресурса
    
    push_task(task);
  }
}



