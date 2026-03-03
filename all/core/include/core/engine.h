#pragma once 


#include <filesystem>
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

  std::filesystem::path root;
};

}

