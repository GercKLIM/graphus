#include "graph_test.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>


#include "../include/IGraph.h"
#include "../include/ListGraph.h"
#include "../include/MatrixGraph.h"
#include "../include/SetGraph.h"
#include "../include/ArcGraph.h"

/* Вспомогательные функции */

// Сортировка и проверка вектора с выводом информации об ошибке
void SortAndAssert(const std::vector<int>& expected, const std::vector<int>& actual,
                   const std::string& testName, int vertex, int& failedTestCount) {
    std::vector<int> actualCopy = actual;
    std::sort(actualCopy.begin(), actualCopy.end());

    if (expected != actualCopy) {
        std::cerr << "[TEST FAILED] " << testName << "\n";
        std::cerr << "Vertex: " << vertex << "\n";

        std::cerr << "Expected: ";
        for (int v : expected) {
            std::cerr << v << " ";
        }
        std::cerr << "\nActual:   ";
        for (int v : actualCopy) {
            std::cerr << v << " ";
        }
        std::cerr << "\n\n";

        ++failedTestCount;
    }
}

/* Тесты для всех реализаций графа */

// Тест 1: Проверка пустого графа
template <typename GraphType>
void TestEmptyGraph(int& failedTestCount) {
    GraphType graph(5);  // Граф из 5 вершин без рёбер

    assert(graph.VerticesCount() == 5);

    for (int i = 0; i < 5; ++i) {
        SortAndAssert({}, graph.GetNextVertices(i), "GetNextVertices", i, failedTestCount);
        SortAndAssert({}, graph.GetPrevVertices(i), "GetPrevVertices", i, failedTestCount);
    }
}

// Тест 2: Проверка простого графа
template <typename GraphType>
void TestSimpleGraph(int& failedTestCount) {
    GraphType graph(4);

    graph.AddEdge(0, 1);
    graph.AddEdge(0, 2);
    graph.AddEdge(1, 3);
    graph.AddEdge(2, 3);

    SortAndAssert({1, 2}, graph.GetNextVertices(0), "GetNextVertices", 0, failedTestCount);
    SortAndAssert({3}, graph.GetNextVertices(1), "GetNextVertices", 1, failedTestCount);
    SortAndAssert({3}, graph.GetNextVertices(2), "GetNextVertices", 2, failedTestCount);
    SortAndAssert({}, graph.GetNextVertices(3), "GetNextVertices", 3, failedTestCount);

    SortAndAssert({}, graph.GetPrevVertices(0), "GetPrevVertices", 0, failedTestCount);
    SortAndAssert({0}, graph.GetPrevVertices(1), "GetPrevVertices", 1, failedTestCount);
    SortAndAssert({0}, graph.GetPrevVertices(2), "GetPrevVertices", 2, failedTestCount);
    SortAndAssert({1, 2}, graph.GetPrevVertices(3), "GetPrevVertices", 3, failedTestCount);
}

// Тест 3: Дублирующиеся ребра
template <typename GraphType>
void TestDuplicateEdges(int& failedTestCount) {
    GraphType graph(3);

    graph.AddEdge(0, 1);
    graph.AddEdge(0, 1);  // Добавляем дубликат

    auto next = graph.GetNextVertices(0);

    std::vector<int> expected;
    if constexpr (std::is_same_v<GraphType, SetGraph> || std::is_same_v<GraphType, MatrixGraph>) {
        expected = {1};
    } else {
        // ListGraph и ArcGraph поддерживают дубликаты
        expected = {1, 1};
    }

    SortAndAssert(expected, next, "GetNextVertices", 0, failedTestCount);
}

// Тест 4: Изолированные вершины
template <typename GraphType>
void TestIsolatedVertices(int& failedTestCount) {
    GraphType graph(5);

    graph.AddEdge(0, 1);
    graph.AddEdge(2, 3);

    SortAndAssert({1}, graph.GetNextVertices(0), "GetNextVertices", 0, failedTestCount);
    SortAndAssert({}, graph.GetNextVertices(4), "GetNextVertices", 4, failedTestCount);
    SortAndAssert({}, graph.GetPrevVertices(4), "GetPrevVertices", 4, failedTestCount);
}

// Тест 5: Копирование графа через конструктор
template <typename GraphType>
void TestCopyConstructor(int& failedTestCount) {
    GraphType original(4);
    original.AddEdge(0, 1);
    original.AddEdge(1, 2);
    original.AddEdge(2, 3);

    IGraph& baseRef = original;
    GraphType copy(baseRef);

    assert(copy.VerticesCount() == 4);
    SortAndAssert({1}, copy.GetNextVertices(0), "GetNextVertices", 0, failedTestCount);
    SortAndAssert({2}, copy.GetNextVertices(1), "GetNextVertices", 1, failedTestCount);
    SortAndAssert({3}, copy.GetNextVertices(2), "GetNextVertices", 2, failedTestCount);
    SortAndAssert({}, copy.GetNextVertices(3), "GetNextVertices", 3, failedTestCount);
}

// Тест 6: Циклический граф
template <typename GraphType>
void TestCyclicGraph(int& failedTestCount) {
    GraphType graph(3);

    graph.AddEdge(0, 1);
    graph.AddEdge(1, 2);
    graph.AddEdge(2, 0);  // Цикл

    SortAndAssert({1}, graph.GetNextVertices(0), "GetNextVertices", 0, failedTestCount);
    SortAndAssert({2}, graph.GetNextVertices(1), "GetNextVertices", 1, failedTestCount);
    SortAndAssert({0}, graph.GetNextVertices(2), "GetNextVertices", 2, failedTestCount);

    SortAndAssert({2}, graph.GetPrevVertices(0), "GetPrevVertices", 0, failedTestCount);
    SortAndAssert({0}, graph.GetPrevVertices(1), "GetPrevVertices", 1, failedTestCount);
    SortAndAssert({1}, graph.GetPrevVertices(2), "GetPrevVertices", 2, failedTestCount);
}

// Тест 7: Полный граф (все со всеми)
template <typename GraphType>
void TestCompleteGraph(int& failedTestCount) {
    const int N = 4;
    GraphType graph(N);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i != j) {
                graph.AddEdge(i, j);
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        std::vector<int> expected;
        for (int j = 0; j < N; ++j) {
            if (i != j) expected.push_back(j);
        }
        SortAndAssert(expected, graph.GetNextVertices(i), "GetNextVertices", i, failedTestCount);
    }
}

// Тест 8: Большие данные
template <typename GraphType>
void TestLargeGraph(int& failedTestCount) {
    const int N = 1000;
    GraphType graph(N);

    for (int i = 0; i < N - 1; ++i) {
        graph.AddEdge(i, i + 1);
    }

    for (int i = 0; i < N - 1; ++i) {
        SortAndAssert({i + 1}, graph.GetNextVertices(i), "GetNextVertices", i, failedTestCount);
    }
    SortAndAssert({}, graph.GetNextVertices(N - 1), "GetNextVertices", N - 1, failedTestCount);
}

// Запуск всех тестов
template <typename GraphType>
void RunAllTestsForGraph(const std::string& name, int& failedTestCount) {
    std::cout << "=== Testing " << name << " ===\n";

    TestEmptyGraph<GraphType>(failedTestCount);
    TestSimpleGraph<GraphType>(failedTestCount);
    TestDuplicateEdges<GraphType>(failedTestCount);
    TestIsolatedVertices<GraphType>(failedTestCount);
    TestCopyConstructor<GraphType>(failedTestCount);
    TestCyclicGraph<GraphType>(failedTestCount);
    TestCompleteGraph<GraphType>(failedTestCount);
    TestLargeGraph<GraphType>(failedTestCount);

    std::cout << "All tests passed for " << name << "\n\n";
}

// Главная функция
int test() {
    int failedTestCount = 0;

    std::cout << "=== START TESTING ===\n\n";

    RunAllTestsForGraph<ListGraph>("ListGraph", failedTestCount);
    RunAllTestsForGraph<MatrixGraph>("MatrixGraph", failedTestCount);
    RunAllTestsForGraph<SetGraph>("SetGraph", failedTestCount);
    RunAllTestsForGraph<ArcGraph>("ArcGraph", failedTestCount);

    if (failedTestCount == 0) {
        std::cout << "=== ALL TESTS PASSED ===\n";
    } else {
        std::cerr << "Failed " << failedTestCount << " test(s).\n";
    }

    return failedTestCount > 0 ? 1 : 0;
}