cmake_minimum_required(VERSION 3.10)

project(lab11 LANGUAGES CXX)

# Используем C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пути к заголовкам
include_directories(include)

# Собираем все cpp-файлы автоматически
file(GLOB SOURCES
    "src/*.cpp"
)

# Создаем исполняемый файл
add_executable(lab11 ${SOURCES})
