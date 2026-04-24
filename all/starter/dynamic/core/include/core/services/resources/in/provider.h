#pragma once 


#include "manager.h"
#include "sfr/core/resources/IStream.h"
#include "sfr/core/resources/states.h"
#include <memory>
#include <string_view>


//#############3
// Провайдеры - обьекты предоставлающие доступ 
// к получению ресурсов из разных источников,одним и тем же логичесикм действием
//#############3


class IvfsProvider{
public:  
  friend class ResourceManager;
  
  virtual ~IvfsProvider() = default;

  virtual std::unique_ptr<IStream> OpenStream(
    const std::string_view,
    const ResourceTaskType 
  );

  virtual bool canHandle(
    const std::string_view uri
  ) const = 0; 
  
private:

  

};



