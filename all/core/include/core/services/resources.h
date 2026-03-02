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
#include <thread>
#include <unordered_map>


class IResource;

using ResourceCreator = 
std::function<IResource*(const std::filesystem::path&)>;

typedef enum {
    RES_STATE_EMPTY = 0,      // Объект создан, но еще не в очереди
    RES_STATE_IN_QUEUE,       // Ждет свободного воркера
    RES_STATE_LOADING,        // Воркер прямо сейчас читает данные
    RES_STATE_SUCCESS,        // Полностью готов к работе
    
    // Группа ошибок:
    RES_STATE_ERROR_NOT_FOUND,      // Файл физически пропал
    RES_STATE_ERROR_FORMAT,         // stbi_load вернул nullptr (битый файл)
    RES_STATE_ERROR_MEMORY,         // Не хватило RAM/VRAM
    RES_STATE_ERROR_UNKNOWN_TYPE,   // Нет креатора для такого расширения
    RES_STATE_ERROR_INTERNAL,        // Что-то пошло не так в самом менеджере, 
    RES_StATE_OS_ERROR              // операционная систем отказала
} ResourceState;


class ResourceManager{
public:
  //// Стандартные функции
  
  // Инициализация 
  static void init(); 

  // Отключение
  static void shutdown(); 
  
  // Создание ресурса
  static RESULT_CODE create(const std::filesystem::path& path,IResource** out);
  
  // Создание ресурса (синхронный вариант)
  static RESULT_CODE wait_create(const std::filesystem::path& path,IResource** out);

  // Функция для воркера 
  static void resource_worker();
  
  // Функция для регистрации типа ресурса
  static void register_creator( 
    std::string,
    ResourceCreator
  );

private:
  // Отдельный поток 
  static std::thread worker;   
  static std::mutex mtx;
  static std::atomic<bool> should_run; 
  static std::condition_variable_any resource_cv;  
  
  // Очередь 
  static std::queue<IResource*> load_queue;

  // Хранилище 
  static std::unordered_map<std::filesystem::path, IResource*> storage; 
  
  // Реестр типов ресурсов 
  static std::unordered_map<std::string,ResourceCreator> creators;

};

class IResource{
  public:
    friend class ResourceManager;

    virtual void load() = 0;

    virtual ~IResource() = 0;
    
    IResource(std::filesystem::path p,std::string_view ext);
    
    ResourceState getStatus();
    
  protected:
    std::filesystem::path path;
    uint32_t filesize;
    std::string ext;

    std::atomic<uint32_t> ref_count; 
    std::atomic<ResourceState> state;
};



