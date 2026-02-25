#pragma once 


#include <atomic>
#include <condition_variable>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <unordered_map>


class IResource;

class ResourceManager{
public:
  enum State{
    Success,
    Load,
    Error 
  };

  // Стандартные функции
  static void init();

  static void shutdown();
  
  // Функция загрузки ресурса
  static IResource* load(std::filesystem::path path);
  
  // Функция для воркера 
  static void resource_worker();

private:
  // Отдельный поток 
  static std::thread worker;   
  static std::mutex mtx;
  static std::atomic<bool> should_run; 
  static std::condition_variable_any resource_cv;  
  
  // Очередь 
  std::queue<IResource*> load_queue;

  // Хранилище 
  static std::unordered_map<std::string, IResource*> storage; 
  

};


class IResource{
  public:
    friend class ResourceManager;

    virtual void load() = 0;

    virtual ~IResource() = default;


  private:
    std::atomic<ResourceManager::State> state;
    std::size_t filesize;
    std::filesystem::path path;
    std::atomic<uint32_t> ref_count;
 
};



