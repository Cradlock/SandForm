#include "core/log.h"
#include "core/utils.h"
#include <atomic>
#include <condition_variable>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <queue>
#include <string>
#include <string_view>
#include <iostream>
#include <thread>
#include <utility>

// Инициализация статических данных

std::queue<Logger::LogEntry> Logger::log_queue;
std::mutex Logger::log_queue_mutex;
std::thread Logger::log_worker;
std::condition_variable_any Logger::log_cv; 
std::atomic<bool> Logger::should_run{false};




void Logger::init(){
  // Создание папки logs   
  std::filesystem::path logs_dir = "logs/";
  if(!std::filesystem::exists(logs_dir)){
    std::filesystem::create_directories(logs_dir);
  }
  
  // запуска потока 
  log_worker = std::thread(&Logger::log_writer);

}

void Logger::shutdown(){
  // Чтобы отметить что новых логов уже не будет
  should_run = false;
  
  // Будим поток чтобы тот проверил условие should_run 
  log_cv.notify_all();

  if(log_worker.joinable()){
    log_worker.join();
  }
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


void Logger::write_log(
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
  write_log("logs/fatal.log","FATAL",msg);
}


void Logger::error(std::string_view msg){
  write_log("logs/error.log","ERROR",msg);
}



void Logger::warning(std::string_view msg){
  async_log(msg, TypeLog::WARNING);
}

void Logger::info(std::string_view msg){
  async_log(msg, TypeLog::INFO);
}



// Функция для отдельного потока
void Logger::log_writer(){
  
  while (should_run || !log_queue.empty()) {
    LogEntry entry;

    {
      std::unique_lock<std::mutex> lock(log_queue_mutex);
      log_cv.wait(lock,[] { 
          return !should_run || !log_queue.empty(); 
      });
        
      if(log_queue.empty() && !should_run) break;
      
      entry = std::move(log_queue.front());
      log_queue.pop();
    }
    
    std::string filename;
    std::string prefix; 
    
    switch (entry.type) {
      case Logger::TypeLog::INFO:
        filename = "logs/info.log";
        prefix = "INFO";
        break; 
      case Logger::TypeLog::WARNING:
        filename = "logs/warning.log";
        prefix = "WARNING";
        break;
      default: break;
    }

    write_log(filename,prefix,entry.msg);

  }
}

void Logger::async_log(std::string_view msg,TypeLog type){
  {
    std::lock_guard<std::mutex> lock(log_queue_mutex);
    log_queue.push({
        std::string(msg),type,get_current_time()});
  }
  log_cv.notify_one();
}


