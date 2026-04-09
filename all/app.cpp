#include "core/engine.h"
#include "core/error.h"
#include "core/services/log.h"
#include "core/utils.h"
#include "plugin_manager/manager.h"
#include "logic/hello/hello.h"
// Основной двигатель
core::Engine engine;

// Менеджер плагинов
PluginManager plugin_manager("modules.json","modules");

int main(){ 
  
  logic_hello();

  engine.Init(); 
   
  RESULT_CODE status_pl_manager = plugin_manager.init(engine.getRoot());  
  
  engine.Shutdown();  
  return 0;
}




