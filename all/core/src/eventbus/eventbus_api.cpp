





#include "core/error.h"
#include "core/services/eventbus.h"
#include <cstdint>
#include <mutex>
#include <shared_mutex>
#include <utility>
#include <vector>





Token EventBus::subscribe(
  uint32_t event_id,
  Callback func
){
  std::unique_lock lock(mtx);
  uint32_t unique_id = nextToken++;
  
  Token t = (static_cast<uint64_t>(event_id) << 32) | unique_id;
  storage[event_id][t] = std::move(func);
  return t;
}

void EventBus::unsubscribe(
  Token token
){ 
  std::unique_lock lock(mtx);
  uint32_t eventId = static_cast<uint32_t>(token >> 32);
  
  auto it = storage.find(eventId);
  if (it != storage.end()) {
    it->second.erase(token);
  }
}


uint64_t EventBus::publish(
  uint32_t event_id, 
  void* data
){
  std::vector<Callback> to_call;

  {
    std::shared_lock lock(mtx);
    auto it = storage.find(event_id);
    if(it != storage.end()){
      to_call.reserve(it->second.size());
      for(auto const&[token,cb] : it->second){
        to_call.push_back(cb);
      }
    }
    

  }
  
  
  for(auto& cb : to_call){
    cb(data);
  }

  return static_cast<uint64_t>(to_call.size());
}





