#include "core/services/eventbus.h"
#include <atomic>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <shared_mutex>
#include <unordered_map>



std::filesystem::path EventBus::root;

std::unordered_map<
  uint32_t, 
  std::unordered_map<
    uint32_t,
    Callback
  >> EventBus::storage;

std::atomic<uint32_t> EventBus::nextToken = 0;

void EventBus::init(
  const std::filesystem::path& root_p
){
  root = root_p;

}


void EventBus::shutdown(){

}















