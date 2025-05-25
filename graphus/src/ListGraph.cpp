#include "../include/ListGraph.h"


// Конструктор графа с заданным количеством вершин без ребер
ListGraph::ListGraph(int verticesCount) {
    adjacencyList.resize(verticesCount);  // Инициализируем вектор нужным количеством вершин
}

// Конструктор копирования
ListGraph::ListGraph(const IGraph& other) {
    // Подготавливаем структуру под новый граф
    adjacencyList.resize(other.VerticesCount());
    // Вызываем общий метод копирования через интерфейс
    IGraph::CopyFrom(other);
}


/* Методы интерфейса */


// Метод добавления ребра в граф
void ListGraph::AddEdge(int from, int to) {
    adjacencyList[from].push_back(to);  // Добавляем 'to' в список исходящих рёбер из 'from'
}

// Метод, возвращающий значение кол-ва вершин графа
int ListGraph::VerticesCount() const {
    return adjacencyList.size();
}

// Метод, возвращающий список вершин в которые можно прийти из заданной вершины vertex
std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    // Возвращаем копию вектора исходящих рёбер
    return adjacencyList[vertex];
}

// Возвращает список вершин, из которых можно прийти в заданную вершину vertex
std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;

    for (int v = 0; v < adjacencyList.size(); ++v) {
        for (int u : adjacencyList[v]) {
            if (u == vertex) {
                // Нашли входящее ребро из v в vertex
                result.push_back(v);
                break;
            }
        }
    }

    return result;
}