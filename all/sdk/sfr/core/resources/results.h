#pragma once 


#include "sfr/common/status_codes.h"
#include "sfr/core/resources/Interface.h"
#include "sfr/core/resources/states.h"
#include <cstddef>
#include <cstdint>





// [Оболочка ресурса]
typedef struct ResResource {
  RESULT_CODE code;
  Resource* resource;
} ReqResource;



// [Оболочка Json узла]
typedef struct ResJsonNode {
  RESULT_CODE code;

} ReqJsonNode;

// [Оболочка used bytes]
typedef struct ResUsedBytes {
  RESULT_CODE code;
  size_t size;
} ResUsedBytes;

// [Оболочка Bytes offset]
typedef struct ResOffsetBytes {
  RESULT_CODE code;
  int offset;
} ResOffsetBytes; 

// [Оболочка is_valid]
typedef struct ResValid {
  RESULT_CODE code;
} ResValid;

// [Оболчка размера]
typedef struct ResSize {
  RESULT_CODE code;
  int64_t size;
} ResSize;


// [Оболочка IStream]
typedef struct ResStream {
  RESULT_CODE code;
  IStream* stream;
} ResStream;




