#pragma once 



#include "core/services/resources.h"
#include <array>
#include <filesystem>
#include <string>


class JsonResource : public IResource{
public:
  using IResource::IResource;

  ~JsonResource() override;

  void load() override;
  
  
  static bool is_this(std::string_view ext);

    
};
