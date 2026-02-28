#include "core/engine.h"
#include "core/services/log.h"
#include "plugin_manager/manager.h"

// Основной двигатель
core::Engine engine;

// Менеджер плагинов
PluginManager plugin_manager("modules.json","modules");

int main(){ 
  
  engine.Init(); 
  if(!plugin_manager.init()){
    return -1;
  }
  

  
  
  engine.Shutdown();  
  return 0;
}




