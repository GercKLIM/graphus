#pragma once
#include "IGraph.h"
#include <vector>
#include <set>

// Класс SetGraph - Реализация ориентированного графа с использованием
// множества исходящих рёбер для каждой вершины
class SetGraph : public IGraph {
private:
    std::vector<std::set<int>> adjacencySets;

public:
    // Конструктор графа с заданным количеством вершин без ребер
    explicit SetGraph(int verticesCount);

    // Конструктор копирования
    SetGraph(const IGraph& other);

    // Запрещаем оператор присваивания
    SetGraph& operator=(const SetGraph&) = delete;


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