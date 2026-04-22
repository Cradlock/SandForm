#pragma once 





#include <cstdint>
#include <sfr/core/resources/Interface.h>
#include <sfr/core/resources/states.h>
#include <atomic>
#include <filesystem>
#include <string>
#include <string_view>


class ResourceInternal{
public:
  Resource pub;

private:

  std::atomic<int> ref_count{1};
  std::filesystem::path fullpath;

  ResourceState state{ResourceState::RES_STATE_EMPTY};
  const ResourceVtable vtable;
  
  std::string resource_type;

public:
  ResourceInternal(uint32_t,const char*);
  static ResourceInternal* from_res(Resource*);


public:
  ResourceState getState() const noexcept { return this->state; };
  Resource* getPublic() noexcept { return &this->pub; };
  std::string_view getResourceType() noexcept { return this->resource_type; };

};




