#include "core/engine.h"
#include "core/config.h"
#include "core/eventbus.h"
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
  
  // Шина событий 
  EventBus::init();
}


void core::Engine::Shutdown(){
// В обратном порядке инициалиазции

  EventBus::shutdown();

  Config::shutdown();

  ResourceManager::shutdown();

  Logger::shutdown();

}
