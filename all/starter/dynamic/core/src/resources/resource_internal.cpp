



#include "core/services/resources/in/resource.h"
#include "sfr/core/resources/Interface.h"
#include <cstdint>
#include <filesystem>


ResourceInternal::ResourceInternal(
  uint32_t type,
  const char* path,
  ResourceVtable vtable_p
) :
fullpath(path),vtable(vtable_p)
{
  
};



ResourceInternal* ResourceInternal::from_res(Resource* resource){
  if(!resource) return nullptr;


};

