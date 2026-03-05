#pragma once 





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
    RES_StATE_OS_ERROR,              // операционная систем отказала
    RES_StATE_WRITE_ERROR            // Ошибка записи
                                  
} ResourceState;



typedef enum {
  SYNC,
  ASYNC 
} ResourceLoadType;

typedef enum {
  LOAD,
  SAVE,
  CREATE,
  RELEASE,
  DESTROY 
} ResourceTaskType;


