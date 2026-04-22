#pragma once 




#include "sfr/core/resources/results.h"
#include <cstddef>
#include <cstdint>

typedef struct IStream IStream;

typedef struct IStreamVtbl {
  
  ResUsedBytes (*read)(IStream* self,void* buffer,size_t size);

  ResUsedBytes (*write)(IStream* self, const void* buffer, size_t size);

  ResOffsetBytes (*seek)(IStream* self, int64_t offset, int origin);

  ResSize (*tell)(IStream* self);

  ResSize (*size)(IStream* self);

  ResValid   (*is_valid)(IStream* self);

  void   (*close)(IStream* self);

} IStreamVbtl;


// [Поток данных]
typedef struct IStream {
  const IStreamVtbl* vptr; 
} IStream;



