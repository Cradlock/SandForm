


#include "core/error.h"
#include "core/services/config.h"
#include "core/services/log.h"
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
    IResource* base_res = nullptr;
    fs::path path = settings_dir_path / fs::path(name + ".json"); 
    RESULT_CODE code = ResourceManager::create(path,&base_res,ResourceLoadType::SYNC); 
    
    if(code != RESULT_CODE::SUCCESS){
      Logger::log("Error in get config "+name+" with status code "+std::to_string(code),TypeLog::PE_ERROR); 
      return code;
    }
    
    JsonResource* file = static_cast<JsonResource*>(base_res);  
    storage[name] = std::make_unique<ConfigObject>(name,file);

    
    *out = storage[name].get();
    return CREATED_NEW;
  }

// Если есть отдаем его
  *out = it->second.get();
  return SUCCESS;
}




void ConfigObject::save(){

}






