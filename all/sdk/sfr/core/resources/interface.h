#pragma once 

#include <stdint.h>





// Интерфейс для работы с ресурсами 
typedef struct Resource {
  void* data;
  uint32_t size;

} Resource;


// Список функций для каждого ресурса
typedef struct ResourceVtable {
  
} ResourceVtable;


// Функция-фабрика ресурсов 
typedef RESULT_CODE (*ResourceCreator)(const char* path);





