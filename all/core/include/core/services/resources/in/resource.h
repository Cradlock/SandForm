#pragma once 





#include "sfr/core/resources/interface.h"
#include "sfr/core/resources/states.h"
#include <atomic>
#include <filesystem>


class ResourceInternal{
  std::atomic<int> ref_count;
  std::filesystem::path path;
  ResourceState state;
  std::string ext;
  const ResourceVtable vtable;

  Resource pub;
  
  static ResourceInternal from_res(Resource*);

};




