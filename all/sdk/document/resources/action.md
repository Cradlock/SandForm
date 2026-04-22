# Цикл действий




```
rcm->load_async("...");
```

Выбор провайдера:

```
ResourceInternal res;
select_porvider(res.uri);

```

Создание задачи;
```
if(provider.compatable_action(task_type))
Task task(res);
task.stream = provider.OpenStream(res.uri);
```

Добавление задачи:
```
if sync:
action(task);
else if async:
tasks.add(task);
```

Само действие:
action:
    ```
        case LOAD:
            task.res->vtables->load(res->pub);
        ...
    ```




