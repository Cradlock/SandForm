#include <cstdint>
#include <memory>
#include <sfr/common/types.h>
#include "core/services/resources/in/provider.h"
#include "core/services/resources/in/task.h"
#include <array>



namespace fs = std::filesystem;

std::unordered_map<std::string, ResourceInternal*> ResourceManager::storage;

std::queue<Task> ResourceManager::tasks;


std::vector<std::unique_ptr<IvfsProvider>> ResourceManager::providers;


std::unordered_map<uint32_t, ResourceVtable> ResourceManager::vtables;

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


