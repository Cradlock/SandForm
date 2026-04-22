#pragma once 





#include "core/services/resources/in/provider.h"
#include "sfr/core/resources/IStream.h"
#include "sfr/core/resources/states.h"
#include <cstdio>
#include <string>
#include <string_view>


class FileStream : public IStream{
public:
  FILE* handle;
  
  FileStream(const char* path,const char* mode);

  ~FileStream();

};







class FileProvider : public IvfsProvider{
  
  unique_ptr<IStream> OpenStream(
    const std::string_view,
    const ResourceTaskType) override;

  bool canHandle(const std::string_view uri) const override;
    
};


