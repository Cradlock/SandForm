#include "core/error.h"
#include "core/resources_types/json.h"
#include "core/services/log.h"
#include "core/services/resources.h"
#include <algorithm>
#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <iostream>
#include <filesystem>
#include <mutex>
#include <queue>
#include <thread>
#include <unordered_map>

namespace fs = std::filesystem;

std::unordered_map<fs::path, IResource*> ResourceManager::storage;
std::queue<IResource*> ResourceManager::load_queue;
std::unordered_map<std::string, ResourceCreator> ResourceManager::creators;

std::thread ResourceManager::worker;
std::mutex ResourceManager::mtx;
std::atomic<bool> ResourceManager::should_run{false};
std::condition_variable_any ResourceManager::resource_cv;

fs::path ResourceManager::root;


void ResourceManager::init(
  const fs::path& root_p
){
  root = root_p;

  JsonResource::registry();
  
  should_run = true;
  worker = std::thread(resource_worker);
}


void ResourceManager::shutdown(){
  should_run = false; 

  resource_cv.notify_all();

  if(worker.joinable()){
    worker.join();
  }

}


RESULT_CODE ResourceManager::create(
    const fs::path& path,
    IResource** out 
){

// Проверка на аргументы 
  if(!out) return RESULT_CODE::INVALID_PARAMETR;

// Проверка в кеше  
{
  std::lock_guard<std::mutex> lock(mtx);
  auto it = storage.find(path);
  if(it != storage.end()){
    *out = it->second;
    (*out)->ref_count++;
    return RESULT_CODE::SUCCESS;
  }
}

// Проверка существования
  if(!fs::exists(path)){
    Logger::log("file not found:"+path.string(),TypeLog::PE_WARNING);
    return RESULT_CODE::NOT_FOUND;
  }


/// создание нового обьекта

// Подготовка 
  std::string ext = path.extension().string();
  auto c_it = creators.find(ext);
  if(c_it == creators.end()){
    Logger::log("No registered extension:"+ext,TypeLog::PE_WARNING);
    return RESULT_CODE::UNKNOW_EXTENSION;
  }     

// создание и регистрация
  IResource* res = c_it->second(path);
  res->state.store(ResourceState::RES_STATE_IN_QUEUE);
  {
      std::lock_guard<std::mutex> lock(mtx);
      // вторая защита 
      auto it = storage.find(path); 
      if(it != storage.end()){
        delete res;
        *out = it->second;
        (*out)->ref_count++;
        return RESULT_CODE::SUCCESS;
      }
      
      storage[path] = res;
      load_queue.push(res);
  }

  resource_cv.notify_one();
  *out = res;
  return RESULT_CODE::SUCCESS;
}



RESULT_CODE ResourceManager::wait_create(
    const fs::path& path, 
    IResource **out
){
 
// Проверка на аргументы 
  if(!out) return RESULT_CODE::INVALID_PARAMETR;

  if(!fs::exists(path)){
    Logger::log("file not found:"+path.string(),TypeLog::PE_WARNING);
    return RESULT_CODE::NOT_FOUND;
  }

// Проверка в кеше  
  auto it = storage.find(path);
  if(it != storage.end()){
    *out = it->second;
    (*out)->ref_count++;
    return RESULT_CODE::SUCCESS;
  }

// создание нового обьекта
  std::string ext = path.extension().string();
  auto c_it = creators.find(ext);
  
  if(c_it == creators.end()){
    Logger::log("No registered extension:"+ext,TypeLog::PE_WARNING);
    return RESULT_CODE::UNKNOW_EXTENSION;
  }     
  
  IResource* res = c_it->second(path);
  res->load(); 
  *out = res;
  return RESULT_CODE::SUCCESS;
}



void ResourceManager::resource_worker(){
  
  while(true){
    IResource* resourseToLoad = nullptr;

    {
      std::unique_lock<std::mutex> lock(mtx);

      resource_cv.wait(lock,[] {
        return !load_queue.empty() || !should_run;
      });
      
      if(!should_run && load_queue.empty() ){
        break;
      }

      resourseToLoad = load_queue.front();
      load_queue.pop();
    }

    if(resourseToLoad){
      resourseToLoad->load();
    }


  }
  
}




void ResourceManager::register_creator(
  std::string ext, 
  ResourceCreator func
){
  creators[ext] = func;
}




ResourceState IResource::getStatus(){
  return state;
}

std::string IResource::getName(){
  return this->path.filename().string();
}

IResource::IResource(fs::path  p,std::string_view ext_p) : path(p),ext(ext_p) {
  filesize = static_cast<uint32_t>(fs::file_size(p));
}


IResource::~IResource(){
  
}















