
#pragma once 

#include <cstdint>
#include <filesystem>
#include <string>
#include <string_view>

namespace fvn {
  constexpr uint32_t offset_basis = 2166136261u;
  constexpr uint32_t prime = 16777619u;
}


constexpr uint32_t str_to_hash(
  const char* str,
  uint32_t hash = fvn::offset_basis 
){
  return (*str == '\0') 
    ? hash 
    : str_to_hash(str + 1,( hash ^ static_cast<uint32_t>(*str) * fvn::prime));
}



