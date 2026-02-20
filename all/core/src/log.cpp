#include "core/log.h"
#include "core/utils.h"
#include <fstream>
#include <string_view>
#include <iostream>





void Logger::init(){
  std::cout << "Logger init" << std::endl;
  
  
}

void Logger::shutdown(){


}

void Logger::log(
    std::string_view msg, 
    TypeLog type
) {
  switch (type) {
    case Logger::TypeLog::ERROR:
      error(msg); break;

    case Logger::TypeLog::FATAL:
      fatal(msg); break; 
    
    case Logger::TypeLog::INFO:
      info(msg); break;

    case Logger::TypeLog::WARNING:
      warning(msg); break; 

    default:  
      break;;
  }

}


void Logger::write_log_sync(
    std::string_view filename, 
    std::string_view prefix, 
    std::string_view msg){
  
  std::ofstream file(filename.data(),std::ios::app);
  


  if(file.is_open()){
    file <<  '[' << get_current_time() << ']'
          << '[' << prefix << ']' 
          << msg << '\n';
  }

}



void Logger::fatal(std::string_view msg){
  write_log_sync("fatal.log","FATAL",msg);
}


void Logger::error(std::string_view msg){
  write_log_sync("error.log","ERROR",msg);
}



void Logger::warning(std::string_view msg){

}

void Logger::info(std::string_view msg){

}






