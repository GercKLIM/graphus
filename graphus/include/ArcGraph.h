#pragma once
#include "IGraph.h"
#include <vector>
#include <utility>

class ArcGraph : public IGraph {
private:
    std::vector<std::pair<int, int>> edges;
    int verticesCount_;

public:
    // Конструктор графа с заданным количеством вершин без ребер
    explicit ArcGraph(int verticesCount);

    // Конструктор копирования
    ArcGraph(const IGraph& other);

    // Запрещаем оператор присваивания
    ArcGraph& operator=(const ArcGraph&) = delete;


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