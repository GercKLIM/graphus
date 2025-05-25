#pragma once
#include <vector>

// Интерфейс Графа
struct IGraph {
    // Виртуальный деструктор
    virtual ~IGraph() {}

    // Метод добавления ребра в граф
    virtual void AddEdge(int from, int to) = 0;

    // Метод, возвращающий значение кол-ва вершин графа
    virtual int VerticesCount() const = 0;

    // Метод, возвращающий список вершин в которые можно прийти из заданной вершины vertex
    virtual std::vector<int> GetNextVertices(int vertex) const = 0;

    // Возвращает список вершин, из которых можно прийти в заданную вершину vertex
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;

    // Метод копирования графа
    void CopyFrom(const IGraph& other) {
        // Проходим по всем вершинам исходного графа
        for (int v = 0; v < other.VerticesCount(); ++v) {
            // Получаем список вершин, в которые идёт ребро из v
            auto next = other.GetNextVertices(v);

            // Добавляем рёбра в текущий граф
            for (auto u : next) {
                // вызывается виртуальная функция
                AddEdge(v, u);
            }
        }
    }
};
