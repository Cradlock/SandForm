#include "core/engine.h"
#include "core/services/config.h"
#include "core/services/eventbus.h"
#include "core/services/log.h"
#include "core/services/resources.h"
#include "core/utils.h"


core::Engine::Engine(){
  // Вычисляем место нахождение модулей
  root = get_programm_root();  
}


void core::Engine::Init(){
  

  // В первую очередь логгер 
  Logger::init(root / "logs/");
  
  // Менеджер ресурсов
  ResourceManager::init(root);
  
  // Шина событий 
  EventBus::init(root);

  // Потом загружаем конфиги 
  Config::init(root / "settings/");
  
}


void core::Engine::Shutdown(){
// В обратном порядке инициалиазции

  Config::shutdown();
  
  EventBus::shutdown();

  ResourceManager::shutdown();

  Logger::shutdown();

}
