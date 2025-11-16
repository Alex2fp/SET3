# SET3 — исследование алгоритмов MERGE SORT и MERGE+INSERTION SORT

## Структура проекта
- `include/`, `src/` — реализация инфраструктуры (`ArrayGenerator`, `SortTester`) и двух алгоритмов сортировки.
- `apps/analysis.cpp` — консольное приложение для проведения эксперимента и сохранения результатов в `results/measurements.csv`.
- `apps/a2i.cpp` — шаблон решения подзадачи A2i
- `docs/analysis.md` — текстовое описание методики и выводов.

## Сборка
```bash
mkdir -p build
cd build
g++ -std=c++20 -O2 -I../include ../apps/analysis.cpp \
    ../src/ArrayGenerator.cpp ../src/SortTester.cpp ../src/merge_sorts.cpp -o analysis
g++ -std=c++20 -O2 -I../include ../apps/a2i.cpp ../src/merge_sorts.cpp -o a2i
```

## Запуск эксперимента
```bash
./analysis
```
Программа выведет сводную статистику по категориям данных и сохранит полные замеры в `results/measurements.csv`.

## Использование решения
```bash
./a2i
```
На стандартный ввод необходимо подать длину массива и значения элементов. Программа выводит отсортированный массив, используя гибрид MERGE+INSERTION с фиксированным порогом 30.
