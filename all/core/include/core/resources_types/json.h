#pragma once 



#include "core/services/resources.h"
#include <array>
#include <filesystem>
#include <string>
#include <nlohmann/json.hpp>

class JsonResource : public IResource{
public:
  using IResource::IResource;

  ~JsonResource() override;

  void load() override;
  
  void save() override;

  void create() override;

  void destroy() override;

  static void registry();
  
  
private:
  nlohmann::json data;

};
