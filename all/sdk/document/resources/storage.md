# Виртуальное хранение файлов 

У файлов будет свое виртуальное хранилище,в котором они будут ориентироватся по специальному URI:

`{source}://{path}`


* source: Интерфейс в котором хранится файл

* path: Путь к файлу 


### Типы source:

* file: На диске 

* mem: В памяти 

* http,https: Сетевой обьект




### Провайдеры:
Обьекты умеюшие работать с разными типами создания файлов,поддерживают разные операции;

* create 
* save 
* load 
* release




## IStream - поток данных 
Универсальный способо читать данные из разных источников,или сохранять; 





# Инициализация типов ресурсов разных модулей
```
init(ResourceTypeMetadata {
    ResourceSelector {
        extension = png,
    },
    ResourceTypeName "texture",
    ResourceVtable   {...},
});
```
    \
     \
  ```
  create TypeObject = {
    ext             "png",
    name            "texture",
    ResourceVtable  {...},
    module_name     "graphics_directx"
  }
  ```
        \
         \
          \
        ```
        add_types(TypeObject);
        types {
            "png": []
        } 
        ```

























