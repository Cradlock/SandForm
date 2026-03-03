#include "core/services/eventbus.h"
#include <filesystem>
#include <iostream>



std::filesystem::path EventBus::root;


void EventBus::init(
  const std::filesystem::path& root_p
){
  root = root_p;

  std::cout << "EventBus not init" << std::endl;
}


void EventBus::shutdown(){

}

