#pragma once 

#include <stdint.h>
#include <sfr/common/status_codes.h>




// Интерфейс для работы с ресурсами 
typedef struct Resource {
  void* data;

} Resource;


// Список функций для каждого ресурса
typedef struct ResourceVtable {
  // Загрузка
  RESULT_CODE (*load)(const char* path,Resource** out);
  // Создание 
  RESULT_CODE (*create)(const char* path,Resource** out);
  // Сохранение
  RESULT_CODE (*save)(Resource* res);
  // Освобождение 
  void (*release)(Resource* res);

} ResourceVtable;


// Функция-фабрика ресурсов 
typedef Resource* (*ResourceCreator)(const char* path);





