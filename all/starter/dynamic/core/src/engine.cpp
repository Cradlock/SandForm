#include "core/engine.h"
#include "core/services/config/Config.h"
#include "core/services/eventbus/Eventbus.h"
#include "core/services/logger/Logger.h"
#include "core/services/resources/Resources.h"
#include "core/services/tick/Tick.h"
#include "core/utils/prg.h"


core::Engine::Engine(){
  // Вычисляем место нахождение модулей
  root = get_programm_root();  
}

std::filesystem::path core::Engine::getRoot() const {
  return this->root;
}

void core::Engine::Init(){
  

  // В первую очередь логгер 
  Logger::init(root / "logs/");
  
  // Менеджер ресурсов
  ResourceManager::init(root);
  
  // Система тиков
  TickManager::init();

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
