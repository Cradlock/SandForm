#include "core/resources_types/json.h"
#include "core/services/resources.h"
#include <algorithm>
#include <iostream>
#include <filesystem>
#include <unordered_map>


namespace fs = std::filesystem;


std::unordered_map<fs::path, IResource*> ResourceManager::storage;


void ResourceManager::init(){
  
}


void ResourceManager::shutdown(){
  storage.clear();
}




IResource* ResourceManager::create(fs::path path){
  std::string ext = path.extension().string();
  IResource* res = nullptr;
  
  auto it = storage.find(path);
  
  if(it != storage.end()){
    IResource* res = it->second;

    res->ref_count++;

    return res;
  }

  if(JsonResource::is_this(ext)){
      
  }    
  
  return res;
}







IResource::IResource(fs::path  p) : path(p){

}


IResource::~IResource(){

}
