#pragma once 





#define STREAM_CHECK_VALID(handle,res_type) \
  if(!(handle)) { \
   return (res_type){ RESULT_CODE::NOT_FOUND }; \
  }



#define IO_CHECK(res,size,handle) \
  if(res.size < size && ferror(handle)) { \
    res.code = RESULT_CODE::IO_ERROR; \
  }




