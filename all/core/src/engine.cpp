#include "core/engine.h"
#include "core/config.h"
#include "core/log.h"
#include "core/resources.h"


core::Engine::Engine(){

}


void core::Engine::Init(){
  // В первую очередть логгер 
  Logger::init();
  
  // Менеджер ресурсов
  ResourceManager::init();

  // Потом загружаем конфиги 
  Config::init();


}


void core::Engine::Shutdown(){
  

  // В последную очередь Logger 
  Logger::shutdown();

}
