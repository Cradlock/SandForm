#pragma once 


#include "core/error.h"
#include "core/resources_types/json.h"
#include "core/types.h"
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>


class ConfigObject;


class Config{  
private:
  // Папка настроек
  static std::filesystem::path settings_dir_path;
  
  // Хранилище конфигов 
  static std::unordered_map<std::string,
    std::unique_ptr<ConfigObject>> storage;
  
  // Коренной путь
  static std::filesystem::path root;

public:
  
  // Инициализация
  static void init(
    const std::filesystem::path&
  );

  // Отключение от системы
  static void shutdown();
  
  // Попытка подключить файл настроек
  static RESULT_CODE getConfig(std::string name, ConfigObject** out);
 
private:
};




class ConfigObject{
public:
  friend class Config;

  // Конструктор
  ConfigObject(std::string p,JsonResource* file_p);
  
 
  template<typename T>
  RESULT_CODE get(const std::string& path,T* out){
    
    return RESULT_CODE::SUCCESS;
  }
 
  template<typename T>
  RESULT_CODE set(const std::string& path,T* in){
    
    return RESULT_CODE::SUCCESS;
  }
  
  TYPES getType(std::string path);
  
  void save();

  ~ConfigObject();

private:
  JsonResource* file;
  std::string name; 
};














