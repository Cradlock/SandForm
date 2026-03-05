#include "core/resources_types/json.h"
#include "core/services/resources.h"
#include <iostream>



namespace fs = std::filesystem;

std::unordered_map<fs::path, IResource*> ResourceManager::storage;

std::queue<Task> ResourceManager::tasks;

std::unordered_map<
std::string, ResourceCreator> ResourceManager::creators;

std::thread ResourceManager::worker;

std::mutex ResourceManager::mtx_storage;
std::mutex ResourceManager::mtx_tasks;

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


