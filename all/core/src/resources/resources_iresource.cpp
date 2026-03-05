





#include "core/services/resources.h"

namespace fs = std::filesystem;

ResourceState IResource::getStatus(){
  return state;
}

std::string IResource::getName(){
  return this->path.filename().string();
}

IResource::IResource(fs::path  p,std::string_view ext_p) : path(p),ext(ext_p) {
  filesize = static_cast<uint32_t>(fs::file_size(p));
  state.store(ResourceState::RES_STATE_EMPTY);
}


IResource::~IResource(){
  
}




