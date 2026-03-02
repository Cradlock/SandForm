#pragma once 


#include "core/services/resources.h"
#include <cstdint>
#include <string_view>
class TextureResource : public IResource {
public:
  using IResource::IResource; 
  
  ~TextureResource() override;

  void load() override;

  static void registry(); 

  int32_t getWidth();
  int32_t getHeight();


private:

  int32_t width;
  int32_t height;
  int32_t channels;

  unsigned char* data;

  


};



