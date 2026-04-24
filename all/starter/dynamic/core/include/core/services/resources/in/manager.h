#pragma once 


#include <array>
#include <condition_variable>
#include <cstdint>
#include <filesystem>
#include <list>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <string_view>
#include <thread>
#include <unordered_map>
#include <sfr/common/status_codes.h>
#include <utility>
#include <vector>
#include "provider.h"
#include "resource.h"
#include "sfr/common/types.h"
#include "sfr/core/resources/Interface.h"
#include "sfr/core/resources/results.h"
#include "sfr/core/resources/states.h"
#include "task.h"


class IvfsProvider;


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

  // Функция инициализации провайдеров
  static void InitProvider();


public:
//####### [Функции для API ]
  
  // Загрузка ресурса 
  static ResResource load(
    const std::string_view uri,
    ResourceActionType tp
  );

  // Cоздание пустого файла в памяти
  static ResResource create(
    const std::string_view uri,
    ResourceActionType tp
  );
  
  // Сохранение измененении на диске
  static RESULT_CODE save(
    Resource* in,
    ResourceActionType tp
  );
    
  // Функция освобождения ресурса
  static RESULT_CODE release(
    Resource*
  );
 

  
  // ###### [Внутрение Доп функции]
private:

  // #### [Многопоточность]
  
  // Функция для воркера 
  static void resource_worker();
  
  // Логика ожидания
  static void wait_for_resource(Resource*);
  
private:
  // #### [Task]
  
  // Действие 
  static RESULT_CODE action(
    Task 
  );
  
  // Добавление задачи
  static void push_task(Task);

  // Управление задачей
  static void prepare_resource(
    ResourceInternal*,
    ResourceActionType,
    ResourceTaskType
  );
 
private:
  // #### [Работа с ресурсами]

  
  // Отдача обьекта стрима
  static std::pair<RESULT_CODE, std::unique_ptr<IStream>>
    GetStream(std::string_view uri,ResourceTaskType);
  
  
  // Проверка ресурса в кеше   
  static RESULT_CODE get_from_cache(
    std::string_view uri,
    ResourceInternal** out
  );
    
  // Создание или получение обьекта
  static Resource* get_or_create(
    std::string_view uri
  );

   // Проверка расширения
  static RESULT_CODE check_extension(
    const std::string_view
  );

private:
  // ######### [Переменные]

  // Отдельный поток 
  static std::thread worker;   
  static std::mutex mtx_storage;
  static std::mutex mtx_tasks;
  static std::atomic<bool> should_run; 
  static std::condition_variable_any resource_cv;  
  
  // Очередь 
  static std::queue<Task> tasks;
  
  // Хранилище 
  static std::unordered_map<std::string, ResourceInternal*> storage; 
    
  // Провайдеры
  static std::vector<std::unique_ptr<IvfsProvider>> providers;
  
  // Реестр стандартных функций 
  static std::unordered_map<std::uint32_t, ResourceVtable> vtables;
  
  // Реестр типов ресурсов
  static std::unordered_map<std::string, std::uint32_t> res_types;

  // Коренной путь
  static std::filesystem::path root;
  
};






