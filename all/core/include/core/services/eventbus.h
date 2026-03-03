#pragma once 

#include <iostream>
#include <filesystem>
class EventBus{
  

  // Коренной путь
  static std::filesystem::path root;

public:
  EventBus(){

  }

  static void init(
    const std::filesystem::path&
  );
  

  static void shutdown();



};
