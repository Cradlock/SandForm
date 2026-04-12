




#include "sfr/core/resources/states.h"
#include "core/services/resources/Resources.h"


Task::Task(ResourceTaskType type_p,Resource* data_p) :
type(type_p),data(data_p)
{


}


Task::Task(){}

ResourceTaskType Task::getType(){
  return type;
}




Resource* Task::getData(){
  return data;
}

