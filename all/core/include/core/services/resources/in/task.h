#pragma once 


#include "sfr/core/resources/interface.h"
#include "sfr/core/resources/states.h"

class Task{
  public:
    Task();
    Task(ResourceTaskType,Resource*);
    
    ResourceTaskType getType();
    Resource* getData();
  private:
    Resource* data;
    ResourceTaskType type;
};


