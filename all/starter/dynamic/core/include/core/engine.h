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

  
  std::filesystem::path getRoot() const;

private:
  void init_dynamic();

  std::filesystem::path root;
};

}

