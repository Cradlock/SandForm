#pragma once 


#include "core/interfaces/IModule.h"
#include "core/interfaces/ITickable.h"
#include <vector>
namespace core {
class Engine{


public:
  Engine();
  
  // Инициализация всех классов и модулей
  void Init();

  
  // Отключение всех классов и модулей
  void Shutdown();



private:
  void init_dynamic();

  std::vector<IModule*> modules;
  std::vector<ITickable*> tickables;

};

}

