#include <mpi.h>
#include <iostream>
#include <vector>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Номер текущего процесса
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Общее количество процессов

    // Вывод номера и общего числа процессов
    std::cout << "Процесс " << rank << " из " << size << " процессов" << std::endl;

    const int M = 4;  // Число строк матрицы
    const int N = 4;  // Число столбцов матрицы

    // Матрица и вектор определяем на основном процессе
    std::vector<int> A;
    std::vector<int> x(N, 1);  // Пример вектора x (заполняем единицами)
    std::vector<int> y(M, 0);  // Результат умножения
    
    if (rank == 0) {
        // Инициализируем матрицу A на главном процессе
        A = {
            1, 2, 3, 4,
            5, 6, 7, 8,
            9, 10, 11, 12,
            13, 14, 15, 16
        };
    }

    // Определяем количество строк, которые обрабатывает каждый процесс
    int rows_per_process = M / size;
    std::vector<int> local_A(rows_per_process * N);  // Локальная часть матрицы
    std::vector<int> local_y(rows_per_process, 0);   // Локальный результат

    // Разделяем матрицу A по процессам
    MPI_Scatter(A.data(), rows_per_process * N, MPI_INT,
                local_A.data(), rows_per_process * N, MPI_INT, 
                0, MPI_COMM_WORLD);

    // Рассылаем вектор x всем процессам
    MPI_Bcast(x.data(), N, MPI_INT, 0, MPI_COMM_WORLD);

    // Локальное умножение матрицы на вектор
    for (int i = 0; i < rows_per_process; ++i) {
        for (int j = 0; j < N; ++j) {
            local_y[i] += local_A[i * N + j] * x[j];
        }
    }

    // Собираем части результата с каждого процесса в итоговый вектор y
    MPI_Gather(local_y.data(), rows_per_process, MPI_INT,
               y.data(), rows_per_process, MPI_INT, 
               0, MPI_COMM_WORLD);

    // Вывод результата на главном процессе
    if (rank == 0) {
        std::cout << "Результат умножения матрицы на вектор:" << std::endl;
        for (int i = 0; i < M; ++i) {
            std::cout << y[i] << " ";
        }
        std::cout << std::endl;
    }

    MPI_Finalize();
    return 0;
}
