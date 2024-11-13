#include <mpi.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <chrono>

// Параметры для расчета опциона
struct Option {
    double S0;      // Начальная цена актива
    double K;       // Страйк
    double T;       // Время до экспирации
    double r;       // Безрисковая ставка
    double sigma;   // Волатильность
};

// Генератор чисел Соболя для одномерной последовательности
class SobolGenerator1D {
public:
    SobolGenerator1D(int start_index = 1) : index(start_index), direction(1) {}

    // Получаем следующее число Соболя (между 0 и 1)
    double next() {
        int j = 0;
        int i = index;
        while (i & 1) {  // Ищем первый нулевой бит справа
            i >>= 1;
            j++;
        }
        index++;
        direction ^= (1 << j);  // Обновляем направление
        return static_cast<double>(direction) / (1 << 30);
    }

private:
    int index;      // Текущий индекс последовательности Соболя
    int direction;  // Направление вектора для квазислучайного значения
};

// Функция для расчета выплаты по европейскому колл-опциону
double payoff(double S, double K) {
    return std::max(S - K, 0.0);
}

// Основная функция расчета цены опциона методом Монте-Карло
double monteCarloOptionPrice(const Option& option, int num_simulations, int rank, int size) {
    double local_sum = 0.0;
    int local_num_simulations = num_simulations / size;

    // Инициализация генератора Соболя для каждого процесса
    SobolGenerator1D sobol_gen(rank + 1); // Сдвиг последовательности для каждого процесса

    // Вычисления методом Монте-Карло
    for (int i = 0; i < local_num_simulations; ++i) {
        // Получаем квазислучайное число из генератора Соболя
        double U = sobol_gen.next();

        // Вычисляем будущую цену актива S_T
        double ST = option.S0 * exp((option.r - 0.5 * option.sigma * option.sigma) * option.T 
                + option.sigma * sqrt(option.T) * sqrt(-2.0 * log(U)) * cos(2 * M_PI * U));

        // Считаем выплату и добавляем к локальной сумме
        local_sum += payoff(ST, option.K);
    }

    // Усредняем выплаты
    local_sum /= local_num_simulations;

    // Собираем локальные результаты с каждого процесса на главном процессе
    double global_sum = 0.0;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Главный процесс вычисляет итоговую цену опциона
    if (rank == 0) {
        return exp(-option.r * option.T) * global_sum / size;
    }
    return 0.0;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Вывод номера и общего числа процессов
    std::cout << "Процесс " << rank << " из " << size << " процессов" << std::endl;

    // Параметры опциона
    Option option = {100.0, 100.0, 1.0, 0.05, 0.2}; // S0, K, T, r, sigma
    int num_simulations = 1000000;  // Общее число симуляций

    // Измерение времени выполнения
    auto start = std::chrono::high_resolution_clock::now();
    double option_price = monteCarloOptionPrice(option, num_simulations, rank, size);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    // Вывод цены опциона и времени выполнения на главном процессе
    if (rank == 0) {
        std::cout << "Цена европейского опциона: " << option_price << std::endl;
        std::cout << "Время выполнения: " << duration.count() << " секунд" << std::endl;
    }

    MPI_Finalize();
    return 0;
}
