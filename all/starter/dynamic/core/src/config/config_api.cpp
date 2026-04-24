


#include "sfr/common/status_codes.h"
#include "core/services/config/Config.h"
#include "core/services/logger/Logger.h"
#include <memory>

namespace fs = std::filesystem;

RESULT_CODE Config::getConfig(
  std::string name, 
  ConfigObject **out
){
// Проверка на аргументы 
  if(!out) return RESULT_CODE::INVALID_PARAMETR;
// Существование конфига в памяти
  auto it = storage.find(name);
  if(it == storage.end()){
    // Если нет новый конфиг
        return CREATED_NEW;
  }

// Если есть отдаем его
  *out = it->second.get();
  return SUCCESS;
}




void ConfigObject::save(){

}






