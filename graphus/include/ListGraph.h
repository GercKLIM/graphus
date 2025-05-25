#pragma once
#include "IGraph.h"
#include <vector>


// Класс ListGraph - Реализация ориентированного графа с использованием списка смежности.
class ListGraph : public IGraph {
private:
    // adjacencyList — это вектор векторов:
    // - Индекс внешнего вектора соответствует номеру вершины.
    // - Внутренний вектор содержит номера вершин, в которые идут рёбра из текущей.
    std::vector<std::vector<int>> adjacencyList;

public:
    // Конструктор графа с заданным количеством вершин без ребер
    explicit ListGraph(int verticesCount);

    // Конструктор копирования
    ListGraph(const IGraph& other);

    // Запрещаем оператор присваивания
    ListGraph& operator=(const ListGraph&) = delete;


    /* Методы интерфейса */


    // Метод добавления ребра в граф
    void AddEdge(int from, int to) override;

    // Метод, возвращающий значение кол-ва вершин графа
    int VerticesCount() const override;

    // Метод, возвращающий список вершин в которые можно прийти из заданной вершины vertex
    std::vector<int> GetNextVertices(int vertex) const override;

    // Метод, возвращающий список вершин, из которых можно прийти в заданную вершину vertex
    std::vector<int> GetPrevVertices(int vertex) const override;
};