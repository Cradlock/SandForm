



#include "core/resources_types/texture.h"
#include "core/services/resources.h"
#include "core/utils.h"
#include <filesystem>


namespace fs = std::filesystem;

TextureResource::~TextureResource(){

}




void TextureResource::load(){

}

void TextureResource::save(){

}

void TextureResource::destroy(){

}

void TextureResource::registry(){
  auto creator = [] (const fs::path& path) {
    return new TextureResource(path, path.extension().string());
  };

  register_formats(creator,".png",".jpg",".jpeg",".tga",".bmp",".psd");
}





