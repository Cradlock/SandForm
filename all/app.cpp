#include "core/engine.h"
#include "core/services/log.h"
#include "plugin_manager/manager.h"
#include <iostream>

// Основной двигатель
core::Engine engine;

// Менеджер плагинов
PluginManager plugin_manager("modules");

int main(){ 
  
  engine.Init(); 
  if(!plugin_manager.init()){
    std::cout << "Fatal error on PLugin manager (detail on fatal.log )" << std::endl;
    return -1;
  }
  

  
  
  engine.Shutdown();
  
  return 0;
}




