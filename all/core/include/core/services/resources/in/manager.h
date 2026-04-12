#pragma once 


#include <condition_variable>
#include <filesystem>
#include <mutex>
#include <queue>
#include <thread>
#include <unordered_map>
#include <sfr/common/status_codes.h>
#include "resource.h"
#include "sfr/common/types.h"
#include "task.h"

class ResourceManager{
public:
//####### [Функции для engine]
  // Инициализация 
  static void init(
    const std::filesystem::path&
  ); 

  // Отключение
  static void shutdown(); 
 
  // Функция для регистрации типа ресурса
  static void register_creator( 
    const char* ext,
    const ResourceCreator function
  );


public:
//####### [Функции для API ]
  
  // Загрузка ресурса 
  static RESULT_CODE load(
    const std::filesystem::path& path,
    Resource** out,
    ResourceLoadType tp
  );

  // Cоздание пустого файла в памяти
  static RESULT_CODE create(
    const std::filesystem::path&,
    Resource** out,
    ResourceLoadType tp
  );
  
  // Сохранение измененении на диске
  static RESULT_CODE save(
    Resource* in,
    ResourceLoadType tp
  );
   
  // Функция освобождения ресурса
  static RESULT_CODE release(
    Resource*
  );
 

private:
  // ###### [Внутрение Доп функции]

  // Функция для воркера 
  static void resource_worker();
  
  // Действие 
  static RESULT_CODE action(
    Task 
  );
   
  // Проверка ресурса в кеше 
  static RESULT_CODE get_from_cache(
    const std::filesystem::path& path,
    Resource** out
  );
    
  // Создание или получение обьекта
  static Resource* get_or_create(
    const std::filesystem::path&
  );

  // Логика ожидания
  static void wait_for_resource(Resource*);
  
  // Добавление задачи
  static void push_task(Task);

  // Проверка расширения
  static RESULT_CODE check_extension(const std::filesystem::path&);
  
  // Управление задачей
  static void prepare_resource(
    Resource*,
    ResourceLoadType,
    ResourceTaskType
  );

  // Отдельный поток 
  static std::thread worker;   
  static std::mutex mtx_storage;
  static std::mutex mtx_tasks;
  static std::atomic<bool> should_run; 
  static std::condition_variable_any resource_cv;  
  
  // Очередь 
  static std::queue<Task> tasks;

  // Хранилище 
  static std::unordered_map<std::filesystem::path, ResourceInternal*> storage; 
  
  // Реестр типов ресурсов 
  static std::unordered_map<std::string,ResourceCreator> creators;
  
  // Коренной путь
  static std::filesystem::path root;
};






