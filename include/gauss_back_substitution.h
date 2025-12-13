#ifndef GAUSS_BACK_SUBSTITUTION_H
#define GAUSS_BACK_SUBSTITUTION_H

#include <vector>

/**
 * Обратная подстановка (back substitution) для верхнетреугольной матрицы U.
 *
 * Решаем систему Ux = b, где:
 *  - U — квадратная матрица n×n (верхнетреугольная),
 *  - b — вектор длины n,
 *  - на диагонали U[i][i] != 0.
 *
 * Возвращает найденный вектор x.
 */
std::vector<double> backSubstitution(const std::vector<std::vector<double>>& U,
                                     const std::vector<double>& b);

/**
 * Печатает в терминал псевдокод стадии обратной подстановки и объяснение,
 * почему время работы Θ(n^2).
 */
void printBackSubstitutionPseudocodeAndComplexity();

#endif // GAUSS_BACK_SUBSTITUTION_H
