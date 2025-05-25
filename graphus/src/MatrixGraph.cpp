#include "../include/MatrixGraph.h"

// Конструктор графа с заданным количеством вершин без ребер
MatrixGraph::MatrixGraph(int verticesCount)
        : adjacencyMatrix(verticesCount, std::vector<bool>(verticesCount, false)) {}

// Конструктор копирования
MatrixGraph::MatrixGraph(const IGraph& other) {
    // Изменяем размер матрицы под количество вершин исходного графа
    adjacencyMatrix.resize(other.VerticesCount(), std::vector<bool>(other.VerticesCount(), false));

    // Копируем
    CopyFrom(other);
}


/* Методы интерфейса */


// Метод добавления ребра в граф
void MatrixGraph::AddEdge(int from, int to) {
    // Устанавливаем соответствующую ячейку матрицы в true — ребро существует
    adjacencyMatrix[from][to] = true;
}

// Метод, возвращающий значение кол-ва вершин графа
int MatrixGraph::VerticesCount() const {
    // Размер внешнего вектора равен количеству вершин
    return adjacencyMatrix.size();
}

// Метод, возвращающий список вершин в которые можно прийти из заданной вершины vertex
std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    std::vector<int> result;

    // Проходим по всем возможным вершинам-приёмникам
    for (int i = 0; i < adjacencyMatrix[vertex].size(); ++i) {
        // Если ребро из vertex в i существует, то добавляем в результат
        if (adjacencyMatrix[vertex][i])
            result.push_back(i);
    }
    return result;
}

// Метод, возвращающий список вершин, из которых можно прийти в заданную вершину vertex
std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;

    // Проходим по всем возможным вершинам-источникам
    for (int i = 0; i < adjacencyMatrix.size(); ++i) {
        // Если ребро из i в vertex существует, то добавляем в результат
        if (adjacencyMatrix[i][vertex])
            result.push_back(i);
    }
    return result;
}