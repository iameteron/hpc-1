#include <mpi.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

// Функция для разделения массива для алгоритма быстрой сортировки
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Рекурсивная функция быстрой сортировки
void quicksort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Номер текущего процесса
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Общее количество процессов

    // Вывод номера и общего числа процессов
    std::cout << "Процесс " << rank << " из " << size << " процессов" << std::endl;

    const int N = 1000;  // Размер массива
    std::vector<int> arr;

    // Инициализация массива на главном процессе
    if (rank == 0) {
        arr.resize(N);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 10000);

        for (int i = 0; i < N; ++i) {
            arr[i] = dis(gen);
        }

        std::cout << "Несортированный массив: ";
        for (int i = 0; i < 20; ++i) std::cout << arr[i] << " ";
        std::cout << "..." << std::endl;
    }

    // Определение размера подмассива для каждого процесса
    int sub_size = N / size;
    std::vector<int> sub_array(sub_size);

    // Разделение массива между процессами
    MPI_Scatter(arr.data(), sub_size, MPI_INT, sub_array.data(), sub_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Сортировка подмассива на каждом процессе
    quicksort(sub_array, 0, sub_size - 1);

    // Сбор отсортированных подмассивов на главном процессе
    MPI_Gather(sub_array.data(), sub_size, MPI_INT, arr.data(), sub_size, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        // Главный процесс выполняет окончательную сортировку
        std::sort(arr.begin(), arr.end());

        std::cout << "Отсортированный массив: ";
        for (int i = 0; i < 20; ++i) std::cout << arr[i] << " ";
        std::cout << "..." << std::endl;
    }

    MPI_Finalize();
    return 0;
}
