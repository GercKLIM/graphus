#include "../include/SetGraph.h"


// Конструктор графа с заданным количеством вершин без ребер
SetGraph::SetGraph(int verticesCount) : adjacencySets(verticesCount) {}

// Конструктор копирования
SetGraph::SetGraph(const IGraph& other) {
    adjacencySets.resize(other.VerticesCount());
    CopyFrom(other);
}


/* Методы интерфейса */


// Метод добавления ребра в граф
void SetGraph::AddEdge(int from, int to) {
    adjacencySets[from].insert(to);
}

// Метод, возвращающий значение кол-ва вершин графа
int SetGraph::VerticesCount() const {
    return adjacencySets.size();
}

// Метод, возвращающий список вершин в которые можно прийти из заданной вершины vertex
std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    // Преобразуем множество исходящих рёбер в вектор для соответствия интерфейсу
    return std::vector<int>(adjacencySets[vertex].begin(), adjacencySets[vertex].end());
}

// Метод, возвращающий список вершин, из которых можно прийти в заданную вершину vertex
std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;

    // Проходим по всем вершинам графа
    for (int i = 0; i < adjacencySets.size(); ++i) {
        // Если в множестве исходящих ребер вершины i есть vertex,
        // то из i идет ребро в vertex
        if (adjacencySets[i].count(vertex))
            result.push_back(i);
    }
    return result;
}