# MPI Labs

Этот репозиторий содержит реализации лабораторных работ с использованием MPI (Message Passing Interface) для параллельных вычислений в C++. В проекте реализованы следующие задачи:

1. **Умножение матрицы на вектор с использованием MPI и многопоточности.**
2. **Сортировка массива методом Хоара с использованием MPI и многопоточности.**
3. **Вычисление цены европейского опциона методом Монте-Карло с использованием MPI и генератора Соболя для квазислучайных чисел.**

## Компиляция и запуск

### 1. Компиляция программы

Для компиляции каждой из лабораторных работ используйте следующий команду:

- Для **лабораторной работы по умножению матрицы на вектор**:
    ```bash
    mpic++ -o matrix_mult matrix_mult.cpp
    ```

- Для **лабораторной работы по сортировке массива методом Хоара**:
    ```bash
    mpic++ -o quicksort quicksort.cpp
    ```

- Для **лабораторной работы по вычислению цены европейского опциона методом Монте-Карло с генератором Соболя**:
    ```bash
    mpic++ -o monte_carlo_option monte_carlo_option.cpp
    ```

### 2. Запуск программы

Для запуска программы с использованием MPI на нескольких процессах используйте команду `mpirun`:

- Для **умножения матрицы на вектор**:
    ```bash
    mpirun -np <num_processes> ./matrix_mult
    ```

- Для **сортировки массива методом Хоара**:
    ```bash
    mpirun -np <num_processes> ./quicksort
    ```

- Для **вычисления цены опциона методом Монте-Карло**:
    ```bash
    mpirun -np <num_processes> ./monte_carlo_option
    ```

Замените `<num_processes>` на количество процессов, которое вы хотите использовать для выполнения программы. Чем больше процессов, тем быстрее программа будет работать (в зависимости от параллельной масштабируемости задачи).

### 3. Ожидаемый вывод

- В **лабораторной работе по умножению матрицы на вектор** выводятся результаты умножения, а также информация о процессе (номер процесса и общее количество процессов).
  
- В **лабораторной работе по сортировке массива методом Хоара** выводится отсортированный массив и информация о процессе.

- В **лабораторной работе по вычислению цены опциона методом Монте-Карло** выводится вычисленная цена опциона, а также время выполнения на главном процессе.

## Примечания

- Каждая лабораторная работа распараллеливает задачу с использованием MPI и включает параллельные вычисления с использованием разных процессов.
  
- Для генерации чисел Соболя в задаче Монте-Карло используется собственная реализация генератора квазислучайных чисел, обеспечивающая равномерное распределение.

- Время выполнения и эффективность масштабируемости могут зависеть от конфигурации вашего компьютера и количества процессов, с которыми вы запускаете программу.

## Лицензия

Ну какая-то есть