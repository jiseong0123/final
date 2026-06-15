#pragma once

#ifndef WGRAPHMST_H
#define WGRAPHMST_H

#include <iostream>
#include <vector>
using namespace std;

#define MAX_VTXS 100

// --------------------
// Union-Find
// --------------------
class VertexSets {
    int parent[MAX_VTXS];
    int nSets;

public:
    VertexSets(int n) : nSets(n) {
        for (int i = 0; i < n; i++)
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

// --------------------
// Heap Node
// --------------------
class HeapNode {
    int key;

public:
    int v1, v2;

    HeapNode(int k = 0, int u = 0, int v = 0)
        : key(k), v1(u), v2(v) {
    }

    void setNode(int k, int u, int v) {
        key = k;
        v1 = u;
        v2 = v;
    }

    int getKey() {
        return key;
    }

    int getV1() {
        return v1;
    }

    int getV2() {
        return v2;
    }
};

// --------------------
// Min Heap
// --------------------
class MinHeap {
    HeapNode node[MAX_VTXS * MAX_VTXS];
    int size;

public:
    MinHeap() {
        size = 0;
    }

    bool isEmpty() {
        return size == 0;
    }

    void insert(int key, int u, int v) {
        int i = ++size;

        while (i != 1 && key < node[i / 2].getKey()) {
            node[i] = node[i / 2];
            i /= 2;
        }

        node[i].setNode(key, u, v);
    }

    HeapNode remove() {
        HeapNode item = node[1];
        HeapNode temp = node[size--];

        int parent = 1;
        int child = 2;

        while (child <= size) {

            if (child < size &&
                node[child].getKey() > node[child + 1].getKey())
                child++;

            if (temp.getKey() <= node[child].getKey())
                break;

            node[parent] = node[child];

            parent = child;
            child *= 2;
        }

        node[parent] = temp;

        return item;
    }
};

// --------------------
// Weighted Graph MST
// --------------------
class WGraphMST {
    int size;

    // vector 사용
    vector<vector<int>> adj;

public:
    WGraphMST(int n) : size(n) {
        adj.resize(n, vector<int>(n, 0));
    }

    void setEdge(int u, int v, int w) {
        adj[u][v] = w;
        adj[v][u] = w;
    }

    bool hasEdge(int u, int v) {
        return adj[u][v] != 0;
    }

    int getEdge(int u, int v) {
        return adj[u][v];
    }

    void kruskal() {
        MinHeap heap;

        // 모든 간선 삽입
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {

                if (hasEdge(i, j)) {
                    heap.insert(getEdge(i, j), i, j);
                }
            }
        }

        VertexSets set(size);

        int edgeAccepted = 0;

        while (edgeAccepted < size - 1) {

            HeapNode e = heap.remove();

            int uset = set.findSet(e.getV1());
            int vset = set.findSet(e.getV2());

            if (uset != vset) {

                cout << "간선 추가 : "
                    << e.getV1()
                    << " - "
                    << e.getV2()
                    << " (비용 : "
                    << e.getKey()
                    << ")\n";

                set.unionSets(uset, vset);

                edgeAccepted++;
            }
        }
    }
};

#endif