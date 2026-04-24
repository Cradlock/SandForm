#pragma once 


#include "core/services/resources/in/resource.h"
#include <sfr/core/resources/Interface.h>
#include "sfr/core/resources/states.h"

class Task{
  public:
    Task();
    Task(ResourceTaskType,ResourceInternal*);
    
    ResourceTaskType getType();
    ResourceInternal* getData();
  private:
    ResourceInternal* data;
    ResourceTaskType type;
};


