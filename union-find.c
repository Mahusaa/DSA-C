#include <stdio.h>
#include <stdlib.h>

typedef struct UnionFind {
    int size;
    int *componentSize;
    int *parent;
    int numComponents;
} UnionFind;

UnionFind* createUnionFind(int size) {
    if (size <= 0) {
        printf("Invalid size: %d\n", size);
        exit(EXIT_FAILURE);
    }

    UnionFind* uf = (UnionFind*)malloc(sizeof(UnionFind));
    uf->size = uf->numComponents = size;
    uf->componentSize = (int*)malloc(size * sizeof(int));
    uf->parent = (int*)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        uf->parent[i] = i;  // Each element is initially its own parent
        uf->componentSize[i] = 1;  // Each component has one element initially
    }

    return uf;
}

int find(UnionFind* uf, int element) {
    int root = element;
    while (root != uf->parent[root]) root = uf->parent[root];

    while (element != root) {
        int next = uf->parent[element];
        uf->parent[element] = root;
        element = next;
    }

    return root;
}

int isConnected(UnionFind* uf, int element1, int element2) {
    return find(uf, element1) == find(uf, element2);
}

int getComponentSize(UnionFind* uf, int element) {
    return uf->componentSize[find(uf, element)];
}

int getSize(UnionFind* uf) {
    return uf->size;
}

int getNumComponents(UnionFind* uf) {
    return uf->numComponents;
}

void unionElements(UnionFind* uf, int element1, int element2) {
    if (isConnected(uf, element1, element2)) return;

    int root1 = find(uf, element1);
    int root2 = find(uf, element2);

    if (uf->componentSize[root1] < uf->componentSize[root2]) {
        uf->componentSize[root2] += uf->componentSize[root1];
        uf->parent[root1] = root2;
        uf->componentSize[root1] = 0;
    } else {
        uf->componentSize[root1] += uf->componentSize[root2];
        uf->parent[root2] = root1;
        uf->componentSize[root2] = 0;
    }

    uf->numComponents--;
}

void destroyUnionFind(UnionFind* uf) {
    free(uf->componentSize);
    free(uf->parent);
    free(uf);
}

int main() {
    int size = 10;
    UnionFind* uf = createUnionFind(size);

    // Your UnionFind operations go here

    destroyUnionFind(uf);
    return 0;
}

