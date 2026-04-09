#pragma once 

#include "core/error.h"
#include <atomic>
#include <cstdint>
#include <functional>
#include <filesystem>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <unordered_map>
#include <vector>

using Callback = std::function<void(void*)>;
using Token = uint64_t;

class EventBus{
  
  static std::filesystem::path root;

public:

  static void init(
    const std::filesystem::path&
  );
  
  
  static void shutdown();


  static Token subscribe(
    uint32_t, 
    Callback 
  ); 

  static void unsubscribe(
    Token token
  );

  static uint64_t publish(
    uint32_t, 
    void* 
  );
 
private:
  /// Хранилище
  static std::unordered_map<uint32_t,
  std::unordered_map<
    uint32_t,
    Callback>
  > storage; 
  
  /// генератора токенов
  static std::atomic<uint32_t> nextToken;

  // безопасная многопточность
  static inline std::shared_mutex mtx;
  
};


