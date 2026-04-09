#include "core/resources_types/json.h"
#include "core/error.h"
#include "core/resources_types/enums.h"
#include "core/services/log.h"
#include "core/services/resources.h"
#include "core/types.h"
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <exception>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <ostream>
#include <rapidjson/document.h>
#include <rapidjson/error/error.h>
#include <rapidjson/writer.h>
#include <string>

#include <rapidjson/error/en.h>

#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/pointer.h>
#include <type_traits>

namespace fs = std::filesystem;



#define APPLY_TYPES(MACROS) \
  MACROS(double) \
  MACROS(int) \
  MACROS(bool) \
  MACROS(const char*) \
  MACROS(JsonNode) 

TYPES determineType(const rapidjson::Value* v) {
    if (!v) return TYPES::T_UNKNOW;
    if (v->IsObject()) return TYPES::T_OBJECT;
    if (v->IsArray())  return TYPES::T_ARRAY;
    if (v->IsString()) return TYPES::T_STRING;
    if (v->IsInt())    return TYPES::T_INT;
    if (v->IsDouble()) return TYPES::T_DOUBLE;
    if (v->IsBool())   return TYPES::T_BOOL;
    if (v->IsFloat())  return TYPES::T_FLOAT;
    return TYPES::T_UNKNOW;
}

JsonResource::~JsonResource(){

}



JsonResource::JsonResource(const fs::path p) : IResource(p, ".json"){
  doc.SetObject();
}


void JsonResource::load(){
  state.store(ResourceState::RES_STATE_LOADING);
  
  
  
  std::ifstream ifs(this->path);

  if(!ifs.is_open()){
    state.store(ResourceState::RES_STATE_ERROR_NOT_FOUND);
    return;
  }

  
  rapidjson::IStreamWrapper isw(ifs);
  doc.ParseStream(isw);



  if(doc.HasParseError()){
    std::string msg = rapidjson::GetParseError_En(doc.GetParseError());
    Logger::log(
      "Json Parse Error: " + msg
        , TypeLog::PE_WARNING);
    state.store(ResourceState::RES_STATE_ERROR_FORMAT);
    return;
  }

  state.store(ResourceState::RES_STATE_SUCCESS);
  isDirty = false;
}


void JsonResource::save(){
  
    
  std::ofstream ofs(this->path);
  if(!ofs.is_open()){
    state.store(ResourceState::RES_STATE_OS_ERROR);
    return;
  }
  
  rapidjson::OStreamWrapper osw(ofs);
  rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
  doc.Accept(writer);
  isDirty = false;
}


void JsonResource::destroy(){
  state.store(ResourceState::RES_STATE_EMPTY);

  doc.SetNull();

  isDirty = false;
}



void JsonResource::registry(){
  ResourceManager::register_creator(".json", [](const std::filesystem::path& p) {
    return new JsonResource(p); 
  });
}



JsonNode JsonResource::getNode(const char* path){
  JsonNode res;
  res.res = this;
  res.allocator = &doc.GetAllocator();
  
  rapidjson::Value* foundValue = rapidjson::Pointer(path).Get(doc);
  
  if(foundValue != nullptr){
    res.value = foundValue;
    res.tp = determineType(res.value);
  } else {
    res.value = nullptr;
    res.tp = TYPES::T_UNKNOW;
  };

  return res;
}



template<typename T,typename K>
RESULT_CODE JsonResource::get(
  JsonNode node,
  K key,
  T* out
){
  
  rapidjson::Value* v = nullptr;

  if constexpr (std::is_same_v<K, const char*>) {
    if(!node.value->HasMember(key)) return RESULT_CODE::NOT_FOUND;
    v = &((*node.value)[key]);
  } else if constexpr (std::is_integral_v<K>) {
    if(!node.value->IsArray() || key >= node.value->Size()) return RESULT_CODE::OUT_OF_RANGE;
    v = &((*node.value)[key]);
  }

  
  if(!v) return RESULT_CODE::UNKNOW_ERROR;

  
    if constexpr (std::is_same_v<T, int>) {
        if (!v->IsInt()) return RESULT_CODE::WRONG_TYPE;
        *out = v->GetInt();
    } 
    else if constexpr (std::is_same_v<T, const char*>) {
        if (!v->IsString()) return RESULT_CODE::WRONG_TYPE;
        *out = v->GetString();
    }
    else if constexpr (std::is_same_v<T, bool>) {
        if (!v->IsBool()) return RESULT_CODE::WRONG_TYPE;
        *out = v->GetBool();
    }
    else if constexpr (std::is_same_v<T, float>) {
        if (!v->IsNumber()) return RESULT_CODE::WRONG_TYPE;
        *out = v->GetFloat();
    }
    else if constexpr (std::is_same_v<T, JsonNode>) {
        if(!v->IsObject() && !v->IsArray()) {
          return RESULT_CODE::WRONG_TYPE;
        }

        out->res = this;
        out->value = v;
        out->allocator = &doc.GetAllocator();
        out->tp = determineType(v);

    }
  
  return RESULT_CODE::SUCCESS;
}


template<typename T,typename K>
RESULT_CODE JsonNode::get(K key,T* out){
  return this->res->get(*this,key,out);
}; 


template<typename T>
RESULT_CODE JsonNode::get(T *out){
  if(!res || !value) return RESULT_CODE::OBJECT_ERROR_STATE;

    if constexpr (std::is_same_v<T, int>) {
        if (!value->IsInt()) return RESULT_CODE::WRONG_TYPE;
        *out = value->GetInt();
    } 
    else if constexpr (std::is_same_v<T, const char*>) {
        if (!value->IsString()) return RESULT_CODE::WRONG_TYPE;
        *out = value->GetString();
    }
    else if constexpr (std::is_same_v<T, bool>) {
        if (!value->IsBool()) return RESULT_CODE::WRONG_TYPE;
        *out = value->GetBool();
    }
    else if constexpr (std::is_same_v<T, float>) {
        if (!value->IsNumber()) return RESULT_CODE::WRONG_TYPE;
        *out = value->GetFloat();
    }
    else if constexpr (std::is_same_v<T, JsonNode>) {
        if(!value->IsObject() && !value->IsArray()) {
          return RESULT_CODE::WRONG_TYPE;
        }
        
        *out = *this;
    }
  
    return RESULT_CODE::SUCCESS;
};


#define GET_TYPES(TYPE) \
  template RESULT_CODE JsonResource::get<TYPE,const char*>(JsonNode,const char*,TYPE*); \
  template RESULT_CODE JsonResource::get<TYPE,size_t>(JsonNode,size_t,TYPE*); \
  template RESULT_CODE JsonNode::get<TYPE,size_t>(size_t,TYPE*); \
  template RESULT_CODE JsonNode::get<TYPE,const char*>(const char*,TYPE*); \
  template RESULT_CODE JsonNode::get<TYPE>(TYPE*);  

APPLY_TYPES(GET_TYPES);



template<typename T, typename K>
RESULT_CODE JsonResource::set(JsonNode node, K key, T value) {
    if (!node.value) return RESULT_CODE::OBJECT_ERROR_STATE;

    rapidjson::Value* targetValue = nullptr;
    auto& allocator = doc.GetAllocator();

    // 1. Поиск или создание целевого элемента (Value)
    if constexpr (std::is_same_v<std::decay_t<K>, const char*>) {
        if (!node.value->IsObject()) return RESULT_CODE::WRONG_TYPE;
        
        if (!node.value->HasMember(key)) {
            // Если ключа нет, создаем его с null значением
            rapidjson::Value name(key, allocator);
            node.value->AddMember(name, rapidjson::Value().Move(), allocator);
        }
        targetValue = &((*node.value)[key]);
    } 
    else if constexpr (std::is_integral_v<K>) {
        if (!node.value->IsArray()) return RESULT_CODE::WRONG_TYPE;
        if (key >= node.value->Size()) return RESULT_CODE::OUT_OF_RANGE;
        targetValue = &((*node.value)[key]);
    }

    if (!targetValue) return RESULT_CODE::UNKNOW_ERROR;

    // 2. Установка значения в зависимости от типа T
    if constexpr (std::is_same_v<T, int>) {
        targetValue->SetInt(value);
    }
    else if constexpr (std::is_same_v<T, double>) {
        targetValue->SetDouble(value);
    }
    else if constexpr (std::is_same_v<T, bool>) {
        targetValue->SetBool(value);
    }
    else if constexpr (std::is_same_v<T, const char*>) {
        // КРИТИЧНО: Используем SetString с аллокатором, чтобы данные скопировались
        targetValue->SetString(value, allocator);
    }
    else if constexpr (std::is_same_v<T, JsonNode>) {
        // Копируем содержимое другой ноды (глубокое копирование)
        if (value.value) {
            targetValue->CopyFrom(*value.value, allocator);
        } else {
            targetValue->SetNull();
        }
    }

    isDirty = true; // Помечаем ресурс как измененный для сохранения
    return RESULT_CODE::SUCCESS;
}


template<typename T, typename K>
RESULT_CODE JsonNode::set(K key, T value) {
    if (!res) return RESULT_CODE::OBJECT_ERROR_STATE;
    return res->set<T, K>(*this, key, value);
}


#define SET_TYPES(TYPE) \
  template RESULT_CODE JsonResource::set<TYPE,const char*>(JsonNode,const char*,TYPE); \
  template RESULT_CODE JsonResource::set<TYPE,size_t>(JsonNode,size_t,TYPE); \
  template RESULT_CODE JsonNode::set<TYPE,const char*>(const char*,TYPE); \
  template RESULT_CODE JsonNode::set<TYPE,size_t>(size_t,TYPE);  


APPLY_TYPES(SET_TYPES);



template<typename T,typename K>
RESULT_CODE JsonResource::add(
  JsonNode node,
  K key,
  T value 
){
  if (!node.value) return RESULT_CODE::OBJECT_ERROR_STATE;
  auto& allocator = doc.GetAllocator();
  
  if (node.value->IsArray()){
    rapidjson::Value newValue;

    if constexpr (std::is_same_v<T, int>) newValue.SetInt(value);
    else if constexpr (std::is_same_v<T, double>) newValue.SetDouble(value);
    else if constexpr (std::is_same_v<T, bool>) newValue.SetBool(value);
    else if constexpr (std::is_same_v<T, const char*>) newValue.SetString(value, allocator);
    else if constexpr (std::is_same_v<T, JsonNode>) {
      if (value.value) newValue.CopyFrom(*value.value, allocator);
    }

    node.value->PushBack(newValue, allocator);
    isDirty = true;
    return RESULT_CODE::SUCCESS;
  } else if(node.value->IsObject()){

  }

  return RESULT_CODE::SUCCESS;
};

#define ADD_TYPES(TYPE) \
  template RESULT_CODE JsonResource::add<TYPE,const char*>(JsonNode,const char*,TYPE); \
  template RESULT_CODE JsonResource::add<TYPE,size_t>(JsonNode,size_t,TYPE);
  
  

APPLY_TYPES(ADD_TYPES);


template<typename K>
RESULT_CODE JsonResource::remove(
  JsonNode node,
  K key 
){
  
  return RESULT_CODE::SUCCESS;
};



template RESULT_CODE JsonResource::remove<const char*>(JsonNode,const char*); 
template RESULT_CODE JsonResource::remove<size_t>(JsonNode,size_t);



template<typename K>
RESULT_CODE JsonResource::forEach(
  JsonNode node,
  K key,
  std::function<void(JsonNode)>
){
  
  return RESULT_CODE::SUCCESS;
};



template RESULT_CODE JsonResource::forEach<const char*>(
    JsonNode,
    const char*,
    std::function<void(JsonNode)>
);

template RESULT_CODE JsonResource::forEach<size_t>(
    JsonNode,
    size_t,
    std::function<void(JsonNode)>
);





bool JsonResource::hasPath(const char* key){
 rapidjson::Value* foundValue = rapidjson::Pointer(key).Get(doc);
  return foundValue != nullptr; 
};




