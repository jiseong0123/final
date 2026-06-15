#include <stdio.h>
#include <direct.h>
#include "WGraphMST.h"
#include "WGraphDijkstra.h"

int main() {
    char path[260];
    _getcwd(path, sizeof(path));

    printf("현재 작업 폴더:\n%s\n\n", path);

    WGraphMST mst;

    mst.load("graph.txt");

    printf("\nMST By Kruskal's Algorithm\n");
    mst.Kruskal();

    printf("\nMST By Prim's Algorithm\n");
    mst.Prim(0);

    printf("\n\nShortest Path By Dijkstra Algorithm\n");

    WGraphDijkstra sp;

    sp.load("graph_sp.txt");
    sp.ShortestPath(0);

    return 0;
}