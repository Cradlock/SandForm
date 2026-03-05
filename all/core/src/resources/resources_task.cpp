




#include "core/resources_types/enums.h"
#include "core/services/resources.h"
Task::Task(ResourceTaskType type_p,IResource* data_p) :
type(type_p),data(data_p)
{


}


Task::Task(){}

ResourceTaskType Task::getType(){
  return type;
}




IResource* Task::getData(){
  return data;
}

