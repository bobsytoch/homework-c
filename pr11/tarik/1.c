#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>

int minKey(int V, int key[], bool mstSet[])
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

void printMST(int V, int parent[], int graph[V][V])
{
    printf("Edge \tWeight\n");
    for (int i = 1; i < V - 1; i++)
        printf("%d - %d \t%d \n", parent[i] + 1, i + 1, graph[i][parent[i]]);
}

clock_t primMST(int V, int graph[V][V])
{
    clock_t start = clock();
    int parent[V];
    int key[V];
    bool mstSet[V];

    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(V, key, mstSet);
        mstSet[u] = true;
        for (int v = 0; v < V; v++)
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }
    clock_t end = clock();
    printMST(V, parent, graph);
    return end - start;
}


int maxMatrix(int n, int info[n][3]) {
    int max = 0;
    for (int i = 0; i < n; i++) if (max < info[i][0] || max < info[i][1]) 
        max = info[i][0] > info[i][1] ? info[i][0] : info[i][1];
    return max + 1;
}

void printMatrix(int rows, int cols, int matrix[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%7d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void test(int n, int info[n][3]) {
    int q = maxMatrix(n, info);
    int graph[q][q];
    for (int i = 0; i < q; i++) 
        for (int j = 0; j < q; j++)
            graph[i][j] = 0;

    for (int i = 0; i < n; i++) {
        int u = info[i][0], v = info[i][1], weight = info[i][2];
        graph[u-1][v-1] = graph[v-1][u-1] = weight;
    }

    printf("MATRIX:\n");
    printMatrix(q, q, graph);

    clock_t time = primMST(q, graph);

    printf("Time for calc: %ld microseconds\n\n", time);
}

int main() {
    // start, end, weight
    int info1[11][3] = {
        {1, 2, 7},
        {2, 3, 8},
        {3, 5, 5},
        {5, 2, 7},
        {1, 4, 5},
        {4, 2, 9},
        {4, 5, 15},
        {4, 6, 6},
        {6, 5, 8},
        {5, 7, 9},
        {6, 7, 11},
    };

    test(11, info1);

    // start, end, weight
    int info2[21][3] = {
        {1, 2, 3},  {1, 3, 10}, {1, 4, 5},
        {1, 5, 8},  {1, 6, 7},  {1, 7, 6},
        {2, 3, 12}, {2, 4, 9},  {2, 5, 7},
        {2, 6, 4},  {2, 7, 10}, {3, 4, 11},
        {3, 5, 6},  {3, 6, 8},  {3, 7, 9},
        {4, 5, 7},  {4, 6, 3},  {4, 7, 2},
        {5, 6, 4},  {5, 7, 5},  {6, 7, 1},
    };

    test(21, info2);

    return 0;
}
