# Task_Pools #
### Условие задачи ###

Есть набор бассейнов. Бассейны могут соединяться друг с другом с помощью
каналов. В этом случае они сообщаются друг с другом, и с этого момента
содержащаяся в них вода распределяется в равных пропорциях.

В бассейн может доливаться вода. В этом случае она пропорционально делится между всеми соединёнными бассейнами.

Каналы могут разрываться. В этом случае связи между бассейнами полностью разрываются, т.е. они становятся независимыми. Считаем, что между двумя бассейнами не может быть более одного канала.

Необходимо реализовать функциональность для моделирования этих бассейнов.

Требуемые операции:
1. Добавить воду в бассейн.
2. Соединить 2 бассейна с помощью канала.
3. Разорвать существующие каналы между бассейнами.
4. Показать объём воды в бассейне. 

## Компиляция ##
```
cmake .                - запуск cmake

make                   - сборка проекта

./a.out test.txt       - запуск исполняемого файла для текстового файла
```
