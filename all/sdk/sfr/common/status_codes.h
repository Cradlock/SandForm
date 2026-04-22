#pragma once 


// Общие коды ошибок 
typedef enum {
  SUCCESS,            // успешно
  NOT_FOUND,          // Не найдено 
  INVALID_PARAMETR,   // Неправильные аргументы
  INVALID_PATH,       // Неправильный путь
  UNKNOW_EXTENSION,   // Неизвестный тип
  CREATED_NEW,        // Создан новый обьект
  UNKNOW_ACTION,      // Неизвестное действие
  WRONG_TYPE,         // Неправильный тип
  OUT_OF_RANGE,       // Выходит за границы
  OBJECT_ERROR_STATE, // Обьект не может сделать действие

  UNKNOW_ERROR,       // Неизвестная ошибка
  UNCOMPATABLE_ACTION,// Действие не поддерживается
  IO_ERROR,           // Техническая ошибка ввода-вывода 
  SEEK_ERROR,         // Ошибка перехода курсора 

} RESULT_CODE;


