#pragma once 


#include "core/error.h"
#include <atomic>
#include <condition_variable>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <string_view>
#include <thread>
#include <unordered_map>
#include "core/resources_types/enums.h"

class IResource;

class Task;

using ResourceCreator = 
std::function<IResource*(const std::filesystem::path&)>;


class ResourceManager{
public:
  //// Стандартные функции
  
  // Инициализация 
  static void init(
    const std::filesystem::path&
  ); 

  // Отключение
  static void shutdown(); 
    
  // Загрузка ресурса 
  static RESULT_CODE load(
    const std::filesystem::path& path,
    IResource** out,
    ResourceLoadType tp
  );

  // Cоздание файла физически
  static RESULT_CODE create(
    const std::filesystem::path&,
    IResource** out,
    ResourceLoadType tp
  );

  // Функция для регистрации типа ресурса
  static void register_creator( 
    std::string,
    ResourceCreator
  );
  
  // Функция освобождения ресурса
  static RESULT_CODE release_resource(
    IResource*
  );
  
private:

  // Функция для воркера 
  static void resource_worker();
  
  // Действие 
  static RESULT_CODE action(
    Task 
  );
   
  // Проверка ресурса в кеше 
  static RESULT_CODE get_from_cache(
    const std::filesystem::path& path,
    IResource** out
  );
    
  // Создание или получение обьекта
  static IResource* get_or_create(
    const std::filesystem::path&
  );

  // Логика ожидания
  static void wait_for_resource(IResource*);
  
  // Добавление задачи
  static void push_task(Task);

  // Проверка расширения
  static RESULT_CODE check_extension(const std::filesystem::path&);
  
  // Управление задачей
  static void prepare_resource(
    IResource*,
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
  static std::unordered_map<std::filesystem::path, IResource*> storage; 
  
  // Реестр типов ресурсов 
  static std::unordered_map<std::string,ResourceCreator> creators;
  
  // Коренной путь
  static std::filesystem::path root;

};

class IResource{
  public:
    friend class ResourceManager;

    virtual void load() = 0;
    
    virtual void save() = 0;

    virtual void destroy() = 0;
    
    IResource(std::filesystem::path p,std::string_view ext);
    
    ResourceState getStatus();
    
    std::string getName();

  protected:
    std::filesystem::path path;
    uint32_t filesize;
    std::string ext;

    std::atomic<int32_t> ref_count; 
    std::atomic<ResourceState> state;

    virtual ~IResource() = 0;
};


class Task{
  public:
    Task();
    Task(ResourceTaskType,IResource*);
    
    ResourceTaskType getType();
    IResource* getData();
  private:
    IResource* data;
    ResourceTaskType type;
};


