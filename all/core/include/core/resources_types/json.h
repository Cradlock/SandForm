#pragma once 

#include "core/error.h"
#include "core/services/log.h"
#include "core/services/resources.h"
#include "core/types.h"
#include <cstddef>
#include <cstdint>
#include <deque>
#include <exception>
#include <functional>
#include <memory>
#include <rapidjson/allocators.h>
#include <string>
#include <rapidjson/document.h>


class JsonResource;


struct JsonNode{
    friend class JsonResource;
    
  private:
    JsonResource* res = nullptr;
    rapidjson::Value* value = nullptr;
    rapidjson::Document::AllocatorType* allocator = nullptr;
    
    TYPES tp;
    
  public:

    inline TYPES getType() const {return tp;};
    bool isValid();
    
    template<typename K>
    RESULT_CODE forEach(K,std::function<void(JsonNode*)>);
    
    template<typename T,typename K>
    RESULT_CODE get(K,T*);
    
    template<typename T>
    RESULT_CODE get(T*);

    template<typename T,typename K>
    RESULT_CODE set(K,T);

    template<typename T,typename K>
    RESULT_CODE add(T,K);
    
    template<typename K>
    RESULT_CODE remove(K); 
    
    template<typename K>
    size_t getSize(K);
    
    template<typename K>
    bool empty(K);
    
    template<typename K>
    RESULT_CODE clear(K);
    

};


class JsonResource : public IResource{
public:
  
  JsonResource(const std::filesystem::path p);

  ~JsonResource() override;

  void load() override;
  
  void save() override;

  void destroy() override;
  


  static void registry();
  
public:

  JsonNode getNode(const char* );  

  template<typename T,typename K>
  RESULT_CODE get(JsonNode node,K key,T* out);
  
  template<typename T,typename K>
  RESULT_CODE set(JsonNode node,K key,T value);
 
  template<typename T,typename K>
  RESULT_CODE add(JsonNode node,K key,T value);
  
  template<typename K>
  RESULT_CODE remove(JsonNode node,K key);
  
  template<typename K>
  RESULT_CODE forEach(JsonNode,K,std::function<void(JsonNode)>);


  bool hasPath(const char* path);


private:
  
 


private:
  rapidjson::Document doc;
  bool isDirty = true;

  
};







/*
 * JsonNode* node = res->getNode("/modules");
 * 
 * if(node->getType == TYPES::T_ARRAY){
 *  res->forEach(node,[](JsonNode* obj){});
 * }
 * 
 * 
 * int out;
 * RESULT_CODE code = res->get<int>(node,0,&out);
 * ######################
 * 
 *
 * */




