#pragma once 

#include <cstdint>
#include <stdint.h>
#include <sfr/common/status_codes.h>


// Интерфейс для работы с ресурсами 
typedef struct Resource {
  void* data;  
  const uint32_t type; 

} Resource;




typedef struct IStream IStream;


// Список функций для каждого ресурса
typedef struct ResourceVtable {
  // Загрузка
  RESULT_CODE (*load)(Resource* res,IStream* istr,Resource** out);
  // Создание 
  RESULT_CODE (*create)(IStream* istr,Resource** out);
  // Сохранение
  RESULT_CODE (*save)(Resource* res,IStream* istr);
  // Освобождение 
  void (*release)(Resource* res);

} ResourceVtable;

// Функция-фабрика ресурсов 
typedef Resource* (*ResourceCreator)(const char* path);





