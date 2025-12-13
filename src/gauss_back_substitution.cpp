#include "../include/gauss_back_substitution.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

std::vector<double> backSubstitution(const std::vector<std::vector<double>>& U,
                                     const std::vector<double>& b) {
    std::size_t n = U.size();
    if (n == 0) return {};
    if (b.size() != n) {
        throw std::runtime_error("Размеры U и b не совпадают.");
    }
    for (std::size_t i = 0; i < n; ++i) {
        if (U[i].size() != n) {
            throw std::runtime_error("Матрица U должна быть квадратной n×n.");
        }
    }

    std::vector<double> x(n, 0.0);

    // Идём снизу вверх: i = n-1, n-2, ..., 0
    for (long long i = static_cast<long long>(n) - 1; i >= 0; --i) {
        double sum = 0.0;
        for (std::size_t j = static_cast<std::size_t>(i) + 1; j < n; ++j) {
            sum += U[static_cast<std::size_t>(i)][j] * x[j];
        }
        double diag = U[static_cast<std::size_t>(i)][static_cast<std::size_t>(i)];
        if (diag == 0.0) {
            throw std::runtime_error("Нулевой элемент на диагонали — деление невозможно.");
        }
        x[static_cast<std::size_t>(i)] = (b[static_cast<std::size_t>(i)] - sum) / diag;
    }

    return x;
}

void printBackSubstitutionPseudocodeAndComplexity() {
    std::cout << "\n==============================\n";
    std::cout << "Пункт 5: Обратная подстановка (метод Гаусса)\n";
    std::cout << "==============================\n\n";

    std::cout << "Псевдокод (стадия обратной подстановки для Ux = b):\n";
    std::cout << "-----------------------------------------------\n";
    std::cout << "for i = n-1 .. 0:\n";
    std::cout << "    sum = 0\n";
    std::cout << "    for j = i+1 .. n-1:\n";
    std::cout << "        sum = sum + U[i][j] * x[j]\n";
    std::cout << "    x[i] = (b[i] - sum) / U[i][i]\n";
    std::cout << "-----------------------------------------------\n\n";

    std::cout << "Почему время работы Θ(n^2):\n";
    std::cout << "Внешний цикл выполняется n раз (i = n-1 .. 0).\n";
    std::cout << "Внутри для каждого i выполняется суммирование по j от i+1 до n-1,\n";
    std::cout << "то есть примерно (n-1) + (n-2) + ... + 1 = n(n-1)/2 операций.\n";
    std::cout << "Это квадратичная функция, поэтому сложность Θ(n^2).\n\n";
}
