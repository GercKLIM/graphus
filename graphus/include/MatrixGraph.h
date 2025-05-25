#pragma once
#include "IGraph.h"
#include <vector>

// Класс MatrixGraph - Реализация ориентированного графа через матрицу смежности
class MatrixGraph : public IGraph {
private:
    // adjacencyMatrix — это двумерный вектор булевых значений:
    // - adjacencyMatrix[i][j] == true означает наличие ребра из i в j.
    // - Размер матрицы равен N x N, где N — количество вершин графа.
    std::vector<std::vector<bool>> adjacencyMatrix;

public:
    // Конструктор графа с заданным количеством вершин без ребер
    explicit MatrixGraph(int verticesCount);

    // Конструктор копирования
    MatrixGraph(const IGraph& other);

    // Запрещаем оператор присваивания
    MatrixGraph& operator=(const MatrixGraph&) = delete;


    /* Методы интерфейса */


    // Метод добавления ребра в граф
    void AddEdge(int from, int to) override;

    // Метод, возвращающий значение кол-ва вершин графа
    int VerticesCount() const override;

    // Метод, возвращающий список вершин в которые можно прийти из заданной вершины vertex
    std::vector<int> GetNextVertices(int vertex) const override;

    // Возвращает список вершин, из которых можно прийти в заданную вершину vertex
    std::vector<int> GetPrevVertices(int vertex) const override;
};