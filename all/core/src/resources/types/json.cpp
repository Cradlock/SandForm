#include "core/resources_types/json.h"
#include <string>



JsonResource::~JsonResource(){

}



void JsonResource::load(){


}



bool JsonResource::is_this(std::string_view ext){
  return ext == ".json";
}
