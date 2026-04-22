#include "core/engine.h"
#include <sfr/common/status_codes.h>
#include "core/services/logger/Logger.h"
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




