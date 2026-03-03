#include "core/engine.h"
#include "core/services/log.h"
#include "core/utils.h"
#include "plugin_manager/manager.h"

// Основной двигатель
core::Engine engine;

// Менеджер плагинов
PluginManager plugin_manager("modules.json","modules");

int main(){ 
  
  engine.Init(); 
   
  
  
  engine.Shutdown();  
  return 0;
}




