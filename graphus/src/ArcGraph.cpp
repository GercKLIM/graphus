#include "../include/ArcGraph.h"

// Конструктор графа с заданным количеством вершин без ребер
ArcGraph::ArcGraph(int verticesCount) : verticesCount_(verticesCount) {}

// Конструктор копирования
ArcGraph::ArcGraph(const IGraph& other) {
    verticesCount_ = other.VerticesCount();

    // Проходим по всем вершинам графа
    for (int v = 0; v < other.VerticesCount(); ++v) {
        // Получаем исходящие ребра для текущей вершины
        auto next = other.GetNextVertices(v);

        // Добавляем каждое ребро в граф
        for (auto u : next) {
            AddEdge(v, u);
        }
    }
}


/* Методы интерфейса */


// Метод добавления ребра в граф
void ArcGraph::AddEdge(int from, int to) {
    // Добавляем ребро в список ребер
    edges.emplace_back(from, to);
}

// Метод, возвращающий значение кол-ва вершин графа
int ArcGraph::VerticesCount() const {
    return verticesCount_;
}

// Метод, возвращающий список вершин в которые можно прийти из заданной вершины vertex
std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    std::vector<int> result;

    // Обходим все ребра графа
    for (const auto& edge : edges) {
        // Если это исходящее ребро из vertex, то добавляем в результат
        if (edge.first == vertex)
            result.push_back(edge.second);
    }
    return result;
}

// Метод, возвращающий список вершин, из которых можно прийти в заданную вершину vertex
std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;

    // Обходим все ребра графа
    for (const auto& edge : edges) {
        // Если это входящее ребро в vertex, то добавляем в результат
        if (edge.second == vertex)
            result.push_back(edge.first);
    }
    return result;
}