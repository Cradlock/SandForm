




#include "sfr/core/resources/states.h"
#include "core/services/resources/Resources.h"


Task::Task(ResourceTaskType type_p,ResourceInternal* data_p) :
type(type_p),data(data_p)
{


}


Task::Task(){}

ResourceTaskType Task::getType(){
  return type;
}




ResourceInternal* Task::getData(){
  return data;
}

