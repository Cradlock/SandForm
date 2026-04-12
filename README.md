# Платформа

Этот проект `игровая песочница` 


## Структура

*Код*
```
.
├── app.cpp
├── core
│   ├── CMakeLists.txt
│   ├── include
│   ├── README.md
│   └── src
├── dynamic
│   └── logic
├── plugins
│   ├── input
│   ├── modding
│   ├── render
│   ├── sound
│   └── ui
├── sdk
│   ├── common
│   ├── engine_api.h
│   ├── plugin
│   └── resources
└── static
    └── plugin_manager

```

## Детали структуры 

`app.cpp`: Точка входа -> становится app`.exe/.elf`

`core`: Сердце и ядро движка. (По дефолту динамически слинковано с app) 

`dynamic`: Все что будет динамически слинковано с app 

`plugins`: Плагины (разные динамические библиотеки каждый отвечает за свою функции.
Могут быть написаны на разных языках

`sdk`: Все правила и законы движка 

`static`: Все что статически линукется с app 







