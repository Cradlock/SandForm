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
  static std::unordered_map<std::string, ConfigObject*> storage;
  
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
  
  
};




class ConfigObject{
public:
  
  // Конструктор
  ConfigObject(std::string p,JsonResource* file_p);
  
  // Выдача int 
  RESULT_CODE getInt(std::string path,int* out);
  
  // Выдача string  
  RESULT_CODE getStr(std::string path,std::string* out);
  
  // Выдача float  
  RESULT_CODE getFloat(std::string path,double* out);
 


  // Вставка int 
  RESULT_CODE setInt(std::string path,int in);

  // Вставка string 
  RESULT_CODE setStr(std::string path,std::string in);
  
  // Вставка float 
  RESULT_CODE setFloat(std::string path,double in);
  
  // Проверка типа данных
  TYPES getType(std::string path);

private:
  JsonResource* file;
  std::string name; 
};














