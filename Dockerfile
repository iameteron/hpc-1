# Используем базовый образ Ubuntu
FROM ubuntu:22.04

# Обновляем пакеты и устанавливаем необходимые зависимости
RUN apt-get update && apt-get install -y \
    mpich \
    g++ \
    build-essential \
    sudo \
    && rm -rf /var/lib/apt/lists/*

# Создаем нового пользователя (не root)
RUN useradd -m mpiuser && echo "mpiuser:password" | chpasswd && adduser mpiuser sudo

# Устанавливаем рабочую директорию
WORKDIR /workspace

# Переключаемся на нового пользователя
USER mpiuser

# Запускаем bash
CMD ["/bin/bash"]
