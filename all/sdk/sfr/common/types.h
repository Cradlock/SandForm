#pragma once 


#include "sfr/common/status_codes.h"
#include <cstdint>
typedef enum {
  T_VOID,
  T_UNKNOW,
  T_INT,
  T_FLOAT,
  T_DOUBLE,
  T_STRING,
  T_ARRAY,
  T_BOOL,
  T_JSON_OBJECT
} TYPES;



