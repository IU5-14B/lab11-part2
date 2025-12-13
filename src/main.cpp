#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <random>
#include <iomanip>
#include <algorithm>

#include "../include/avl_tree.h"
#include "../include/two_three_tree.h"
#include "../include/sort_algorithms.h"
#include "../include/gauss_back_substitution.h"

// Печать вектора int
static void printVec(const std::vector<int>& a) {
    for (std::size_t i = 0; i < a.size(); ++i) {
        std::cout << a[i];
        if (i + 1 != a.size()) std::cout << " ";
    }
    std::cout << "\n";
}

// Генерация n различных чисел (перемешанная последовательность 1..n)
static std::vector<int> generateDistinct(std::size_t n, std::mt19937& gen) {
    std::vector<int> v(n);
    for (std::size_t i = 0; i < n; ++i) v[i] = static_cast<int>(i + 1);
    std::shuffle(v.begin(), v.end(), gen);
    return v;
}

int main() {
    std::cout << "Лабораторная работа 11 (ч.2)\n";
    std::cout << "---------------------------------\n\n";

    // -----------------------------
    // Пункт 6: AVL-дерево
    // -----------------------------
    std::mt19937 gen(static_cast<unsigned int>(
        std::chrono::steady_clock::now().time_since_epoch().count()));

    std::size_t n_tree = 15;
    std::cout << "Введите n (кол-во различных чисел) для построения AVL и 2-3 дерева (по умолчанию 15): ";
    std::size_t tmp = 0;
    if (std::cin >> tmp && tmp > 0) n_tree = tmp;
    else {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }

    std::vector<int> treeValues = generateDistinct(n_tree, gen);

    std::cout << "\n[Пункт 6] Построение AVL-дерева из " << n_tree << " различных чисел.\n";
    std::cout << "Вставляемые значения: ";
    printVec(treeValues);

    AVLNode* avlRoot = nullptr;
    for (int val : treeValues) {
        avlRoot = avlInsert(avlRoot, val);
    }
    std::cout << "Обход inorder (должен быть по возрастанию): ";
    inorder(avlRoot);
    std::cout << "\n";
    deleteTree(avlRoot);

    // -----------------------------
    // Пункт 10: 2-3 дерево
    // -----------------------------
    std::cout << "\n[Пункт 10] Построение 2-3-дерева из тех же " << n_tree << " различных чисел.\n";
    Node23* root23 = nullptr;
    for (int val : treeValues) {
        insert23(root23, val);
    }
    std::cout << "Обход inorder (должен быть по возрастанию): ";
    inorder23(root23);
    std::cout << "\n";
    deleteTree23(root23);

    // -----------------------------
    // Пункт 6 (ниже в списке): пирамидальная сортировка + представление пирамиды в виде массива
    // -----------------------------
    std::cout << "\n[Пирамидальная сортировка] Списки из задания (с пошаговым выводом массива-пирамиды):\n";

    std::vector<int> listA = {1, 2, 3, 4, 5};
    std::cout << "\nа) 1 2 3 4 5\n";
    heapSortWithSteps(listA);

    std::vector<int> listB = {5, 4, 3, 2, 1};
    std::cout << "\nб) 5 4 3 2 1\n";
    heapSortWithSteps(listB);

    std::vector<char> listC = {'S', 'O', 'R', 'T', 'I', 'N', 'G'};
    std::cout << "\nв) S O R T I N G\n";
    heapSortCharWithSteps(listC);

    // -----------------------------
    // Пункт 9: три сортировки и исследование производительности
    // -----------------------------
    std::cout << "\n[Пункт 9] Исследование производительности сортировок.\n";
    std::cout << "Размеры: 10^2, 10^3, 10^4, 10^5, 10^6\n";
    std::cout << "Типы входных данных: случайные [1..n], возрастающие, убывающие\n";
    std::cout << "Алгоритмы: merge, quick, heap\n\n";

    std::vector<std::size_t> sizes = {100, 1000, 10000, 100000, 1000000};
    std::vector<std::string> distributions = {"random", "ascending", "descending"};
    std::vector<std::string> algorithms = {"merge", "quick", "heap"};

    std::ofstream fout("results.csv");
    if (!fout) {
        std::cerr << "Ошибка: не удалось открыть results.csv для записи.\n";
        return 1;
    }
    fout << "algorithm,n,distribution,time_ms\n";

    for (const auto& alg : algorithms) {
        for (std::size_t n : sizes) {
            for (const auto& dist : distributions) {
                // Генерация входного массива
                std::vector<int> arr;
                arr.reserve(n);

                if (dist == "random") {
                    std::uniform_int_distribution<> dis(1, static_cast<int>(n));
                    for (std::size_t i = 0; i < n; ++i) {
                        arr.push_back(dis(gen));
                    }
                } else if (dist == "ascending") {
                    for (std::size_t i = 0; i < n; ++i) arr.push_back(static_cast<int>(i + 1));
                } else { // descending
                    for (std::size_t i = 0; i < n; ++i) arr.push_back(static_cast<int>(n - i));
                }

                std::vector<int> toSort = arr;

                auto start = std::chrono::steady_clock::now();
                if (alg == "merge") {
                    mergeSort(toSort, 0, toSort.size() - 1);
                } else if (alg == "quick") {
                    quickSort(toSort, 0, toSort.size() - 1);
                } else {
                    heapSort(toSort);
                }
                auto end = std::chrono::steady_clock::now();

                double elapsed_ms =
                    std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0;

                fout << alg << "," << n << "," << dist << ","
                     << std::fixed << std::setprecision(3) << elapsed_ms << "\n";
                fout.flush();

                std::cout << "Готово: " << alg << ", n=" << n
                          << ", тип=" << dist
                          << ", время=" << elapsed_ms << " мс\n";
            }
        }
    }
    fout.close();
    std::cout << "\nРезультаты записаны в файл results.csv\n";
    std::cout << "Для графиков запусти: python3 scripts/visualize.py results.csv\n";

    // -----------------------------
    // Пункт 5: обратная подстановка Гаусса + Θ(n^2)
    // -----------------------------
    printBackSubstitutionPseudocodeAndComplexity();

    // Мини-демо обратной подстановки на маленьком примере
    std::cout << "Демонстрация на примере (U верхнетреугольная):\n";
    std::vector<std::vector<double>> U = {
        {2, 1, -1},
        {0, 3,  2},
        {0, 0,  4}
    };
    std::vector<double> b = {1, 12, 8};

    try {
        std::vector<double> x = backSubstitution(U, b);
        std::cout << "Решение x:\n";
        for (std::size_t i = 0; i < x.size(); ++i) {
            std::cout << "x[" << i << "] = " << std::fixed << std::setprecision(4) << x[i] << "\n";
        }
    } catch (const std::exception& e) {
        std::cout << "Ошибка при обратной подстановке: " << e.what() << "\n";
    }

    std::cout << "\nГотово.\n";
    return 0;
}
