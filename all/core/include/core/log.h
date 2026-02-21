#pragma once 


#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <string>
#include <string_view>
#include <thread>



class Logger{
public:
  // Функция для инициализации Логгера 
  static void init();
  
  static void shutdown();

  enum TypeLog {
    INFO,
    WARNING,
    ERROR,
    FATAL
  };
  

  struct LogEntry{
    std::string msg;
    TypeLog type;
    std::string datetime;
  };


  static void log(
      std::string_view msg, 
      TypeLog type);


private:
  // статические данные 
  static std::queue<LogEntry> log_queue;
  
  static std::mutex log_queue_mutex;
  static std::thread log_worker;
  static std::condition_variable_any log_cv;
  static std::atomic<bool> should_run;


private:
  // Дополнительные функции
  static void write_log(
      std::string_view filename, 
      std::string_view prefix, 
      std::string_view msg
  );



  static void error(std::string_view);

  static void warning(std::string_view);
  
  static void info(std::string_view);

  static void fatal(std::string_view);
  
  static void log_writer(); 

  static void async_log(std::string_view msg,TypeLog type);
};


