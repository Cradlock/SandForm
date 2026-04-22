
#include "core/services/resources/in/providers/file.h"
#include "macros/files_stream.h"
#include "sfr/common/status_codes.h"
#include "sfr/core/resources/IStream.h"
#include "sfr/core/resources/results.h"
#include "sfr/core/resources/states.h"
#include <cstdint>
#include <cstdio>
#include <exception>
#include <memory>
#include <string>
#include <string_view>



//############################ 
// Функции для File Stream Vtable
//############################


static ResUsedBytes file_read(
  IStream* self,
  void* buffer,
  size_t size 
){
  auto* fs = static_cast<FileStream*>(self);
  
  STREAM_CHECK_VALID(fs->handle,ResUsedBytes);

  ResUsedBytes res = {RESULT_CODE::SUCCESS,0};
  
  res.size = fread(buffer,1,size, fs->handle);
  
  IO_CHECK(res, size, fs->handle)
  return res;
}; 

static ResUsedBytes file_write(
  IStream* self, 
  const void* buffer, 
  size_t size
) {
  auto* fs = static_cast<FileStream*>(self);
    
  STREAM_CHECK_VALID(fs->handle,ResUsedBytes);
      
  ResUsedBytes res = {RESULT_CODE::SUCCESS,0};
    
  res.size = fwrite(buffer, 1, size, fs->handle);
    
  IO_CHECK(res, size, fs->handle)
  return res;
}



static ResOffsetBytes file_seek(
  IStream* self, 
  int64_t offset, 
  int origin
) {
  auto* fs = static_cast<FileStream*>(self);
  STREAM_CHECK_VALID(fs->handle, ResOffsetBytes)
  
  ResOffsetBytes res = {RESULT_CODE::SUCCESS,0};
  
  if(fseek(fs->handle,(long)offset, origin) != 0){
    res.code = RESULT_CODE::SEEK_ERROR;
  } else {
    res.offset = (int)ftell(fs->handle);
  }
  
  return res; 
}

static ResSize file_tell(
  IStream* self
) {
  auto* fs = static_cast<FileStream*>(self);
  STREAM_CHECK_VALID(fs->handle,ResSize)
  
  ResSize res = { RESULT_CODE::SUCCESS,ftell(fs->handle)};
  res.size = ftell(fs->handle); 
  return res;
}

static ResSize file_size(
  IStream* self 
){
  auto* fs = static_cast<FileStream*>(self);
  STREAM_CHECK_VALID(fs->handle,ResSize)  
  
  ResSize res = {RESULT_CODE::SUCCESS,0};
  
  long current = ftell(fs->handle);
  fseek(fs->handle, 0,SEEK_END);
  res.size = ftell(fs->handle);
  fseek(fs->handle,current, SEEK_SET);

  return res;
}

static ResValid file_is_valid(
  IStream* self
){
  auto* fs = static_cast<FileStream*>(self);
  STREAM_CHECK_VALID(fs->handle, ResValid);
  
  ResValid res = {RESULT_CODE::SUCCESS};

  if(ferror(fs->handle)){
    res.code = RESULT_CODE::IO_ERROR;
  }

  return res;
}


static void file_close(IStream* self) {
    auto* fs = static_cast<FileStream*>(self);
    if (fs->handle) {
        fclose(fs->handle);
        fs->handle = nullptr;
    }
}




static const IStreamVbtl g_file_vptr = {
  file_read,
  file_write,
  file_seek,
  file_tell,
  file_size,
  file_is_valid,
  file_close
};

FileStream::FileStream(
    const char* path,
    const char* mode
)
{
  this->vptr = &g_file_vptr;
  this->handle = fopen(path,mode);
}


FileStream::~FileStream(){
  if(this->handle){
    fclose(this->handle);
    this->handle = nullptr;
  }
}




//#######################
// Файловый провайдер
//#######################


std::unique_ptr<IStream> FileProvider::OpenStream(
  const std::string_view uri,
  const ResourceTaskType task_p
){
  const char* mode = "rb";
  switch (task_p) {
    case ResourceTaskType::CREATE:
      mode = "wb";
      break;
    case ResourceTaskType::LOAD: 
      mode = "rb";
      break;
    case ResourceTaskType::RELEASE:
      break;
    case ResourceTaskType::SAVE:
      mode = "ab";
      break;
    default:
      break;
  }

  return std::make_unique<FileStream>(uri.data(),mode);
}


bool FileProvider::canHandle(
  const std::string_view uri 
) const {
  
}



