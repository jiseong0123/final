#pragma once
#pragma warning(disable:4996)

#include <stdio.h>
#include "AdjMatGraph.h"

#define INF 9999
#define MAX_ELEMENT 200

class VertexSets {
    int parent[MAX_VTXS];
    int nSets;

public:
    VertexSets(int n) : nSets(n) {
        for (int i = 0; i < nSets; i++)
            parent[i] = -1;
    }

    bool isRoot(int i) {
        return parent[i] < 0;
    }

    int findSet(int v) {
        while (!isRoot(v))
            v = parent[v];

        return v;
    }

    void unionSets(int s1, int s2) {
        parent[s1] = s2;
        nSets--;
    }
};

class HeapNode {
    int key;
    int v1;
    int v2;

public:
    HeapNode(int k = 0, int u = 0, int v = 0)
        : key(k), v1(u), v2(v) {
    }

    void setKey(int k, int u, int v) {
        key = k;
        v1 = u;
        v2 = v;
    }

    int getKey() { return key; }
    int getV1() { return v1; }
    int getV2() { return v2; }
};

class MinHeap {
    HeapNode node[MAX_ELEMENT];
    int size;

public:
    MinHeap() {
        size = 0;
    }

    bool isEmpty() {
        return size == 0;
    }

    bool isFull() {
        return size == MAX_ELEMENT - 1;
    }

    HeapNode getParent(int i) {
        return node[i / 2];
    }

    void insert(int key, int u, int v) {
        if (isFull()) return;

        int i = ++size;

        while (i != 1 && key < getParent(i).getKey()) {
            node[i] = getParent(i);
            i /= 2;
        }

        node[i].setKey(key, u, v);
    }

    HeapNode remove() {
        HeapNode item = node[1];
        HeapNode last = node[size--];

        int parent = 1;
        int child = 2;

        while (child <= size) {
            if (child < size &&
                node[child].getKey() > node[child + 1].getKey())
                child++;

            if (last.getKey() <= node[child].getKey())
                break;

            node[parent] = node[child];
            parent = child;
            child *= 2;
        }

        node[parent] = last;

        return item;
    }
};

class WGraphMST : public AdjMatGraph {
public:
    void load(const char* filename) {
        FILE* fp = fopen(filename, "r");

        if (fp == NULL) {
            printf("파일 열기 실패\n");
            return;
        }

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

    void Kruskal() {
        MinHeap heap;

        for (int i = 0; i < size - 1; i++) {
            for (int j = i + 1; j < size; j++) {
                if (getEdge(i, j) < INF)
                    heap.insert(getEdge(i, j), i, j);
            }
        }

        VertexSets set(size);
        int edgeAccepted = 0;

        while (edgeAccepted < size - 1 && !heap.isEmpty()) {
            HeapNode e = heap.remove();

            int uset = set.findSet(e.getV1());
            int vset = set.findSet(e.getV2());

            if (uset != vset) {
                printf("간선 추가 : %c - %c (비용:%d)\n",
                    getVertex(e.getV1()),
                    getVertex(e.getV2()),
                    e.getKey());

                set.unionSets(uset, vset);
                edgeAccepted++;
            }
        }
    }
};