#pragma once
#pragma warning(disable:4996)

#include <stdio.h>
#include "AdjMatGraph.h"

#define INF 9999

class WGraphDijkstra : public AdjMatGraph {
    int dist[MAX_VTXS];
    bool found[MAX_VTXS];

public:
    void load(const char* filename) {
        FILE* fp = fopen(filename, "r");

        if (fp == NULL) {
            printf("WGraphDijkstra::load에서 파일 열기 실패: %s\n", filename);
            return;
        }

        printf("WGraphDijkstra::load에서 파일 열기 성공\n");

        reset();

        int n;
        fscanf(fp, "%d", &n);

        for (int i = 0; i < n; i++) {
            char ch;
            fscanf(fp, " %c", &ch);
            insertVertex(ch);
        }

        int weight;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                fscanf(fp, "%d", &weight);

                if (weight == 0)
                    setEdge(i, j, INF);
                else
                    setEdge(i, j, weight);
            }
        }

        fclose(fp);
    }

    int chooseVertex() {
        int min = INF;
        int minpos = -1;

        for (int i = 0; i < size; i++) {
            if (dist[i] < min && !found[i]) {
                min = dist[i];
                minpos = i;
            }
        }

        return minpos;
    }

    void printDistance() {
        for (int i = 0; i < size; i++) {
            if (dist[i] == INF)
                printf("%5s", "INF");
            else
                printf("%5d", dist[i]);
        }

        printf("\n");
    }

    void ShortestPath(int start) {
        for (int i = 0; i < size; i++) {
            dist[i] = getEdge(start, i);
            found[i] = false;
        }

        found[start] = true;
        dist[start] = 0;

        for (int i = 0; i < size - 1; i++) {
            printf("Step%2d :", i + 1);
            printDistance();

            int u = chooseVertex();

            if (u == -1)
                return;

            found[u] = true;

            for (int w = 0; w < size; w++) {
                if (!found[w]) {
                    if (dist[u] + getEdge(u, w) < dist[w])
                        dist[w] = dist[u] + getEdge(u, w);
                }
            }
        }
    }
};