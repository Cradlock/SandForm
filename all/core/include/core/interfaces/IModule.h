#pragma once 



class IModule {
public:
  virtual void init() = 0;
  virtual void shutdown() = 0;
  
  virtual void release() {delete this; }; // Модуль сам знает как себя удалить

  virtual ~IModule(){};
};


