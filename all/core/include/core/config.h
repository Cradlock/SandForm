
#pragma once 


#include <string>

class Config{  
  static std::string settings_filename;
  

public:

  static void init();

  static void shutdown();
  

};

