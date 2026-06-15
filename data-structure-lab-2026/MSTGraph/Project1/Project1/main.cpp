#include "WGraphMST.h"

int main() {
    int n = 5;
    WGraphMST graph(n);

    // 예시 간선
    graph.setEdge(0, 1, 10);
    graph.setEdge(0, 2, 20);
    graph.setEdge(1, 2, 30);
    graph.setEdge(1, 3, 5);
    graph.setEdge(2, 3, 15);
    graph.setEdge(3, 4, 8);

    graph.kruskal();

    return 0;
}