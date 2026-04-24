#include "core/services/logger/Logger.h"
#include "core/utils/time.h"
#include <atomic>
#include <condition_variable>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <ostream>
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


std::filesystem::path Logger::root;

void Logger::init(
  const std::filesystem::path& root_p
) {
  root = root_p;

  // Создание папки logs   
  std::filesystem::path logs_dir = root;
  if(!std::filesystem::exists(logs_dir)){
    std::filesystem::create_directories(logs_dir);
  }
  
  // запуска потока
  should_run = true;
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
    case TypeLog::PE_ERROR:
      error(msg); break;

    case TypeLog::PE_FATAL:
      fatal(msg); break; 
    
    case TypeLog::PE_INFO:
      info(msg); break;

    case TypeLog::PE_WARNING:
      warning(msg); break; 

    default:  
      break;;
  }

}


void Logger::write_log(
    std::string_view filename, 
    std::string_view prefix, 
    std::string_view msg){
  
  std::filesystem::path path = root / filename.data();


  std::ofstream file(path,std::ios::app);
  
  if(file.is_open()){
    file <<  '[' << get_current_time() << ']'
          << '[' << prefix << ']' 
          << msg << '\n';
    
  }

}



void Logger::fatal(std::string_view msg){
  write_log("fatal.log","PE_FATAL",msg);
}


void Logger::error(std::string_view msg){
  write_log("error.log","PE_ERROR",msg);
}



void Logger::warning(std::string_view msg){
  async_log(msg, TypeLog::PE_WARNING);
}

void Logger::info(std::string_view msg){
  async_log(msg, TypeLog::PE_INFO);
}



// Функция для отдельного потока
void Logger::log_writer(){
  
  while (should_run || !log_queue.empty()) {
    LogEntry entry;

    {
      // Ждем пока придут данные или же появится сигнал остановится
      std::unique_lock<std::mutex> lock(log_queue_mutex);
      log_cv.wait(lock,[] { 
          return !should_run || !log_queue.empty(); 
      });
        
      // если данных нет и мы должны остановится выходим из цикла
      if(log_queue.empty() && !should_run) break;
      
      // Если проснулись, но очередь не пуста — забираем лог
      if (!log_queue.empty()) {
        entry = std::move(log_queue.front());
        log_queue.pop();
      } else {
        continue; // На всякий случай, если проснулись по should_run, но очередь пуста
      }
    
    }

    
    std::string filename;
    std::string prefix; 
    
    switch (entry.type) {
      case TypeLog::PE_INFO:
        filename = "info.log";
        prefix = "PE_INFO";
        break; 
      case TypeLog::PE_WARNING:
        filename = "warning.log";
        prefix = "PE_WARNING";
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


