#include "core/engine.h"
#include "core/services/config.h"
#include "core/services/eventbus.h"
#include "core/services/log.h"
#include "core/services/resources.h"


core::Engine::Engine(){

}


void core::Engine::Init(){
  // В первую очередть логгер 
  Logger::init();
  
  // Менеджер ресурсов
  ResourceManager::init();
  
  // Шина событий 
  EventBus::init();

  // Потом загружаем конфиги 
  Config::init();
 
}


void core::Engine::Shutdown(){
// В обратном порядке инициалиазции

  Config::shutdown();
  
  EventBus::shutdown();

  ResourceManager::shutdown();

  Logger::shutdown();

}
