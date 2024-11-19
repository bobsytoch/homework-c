// C code to implement Kruskal's algorithm 
  
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
  
// Comparator function to use in sorting 
int comparator(const void* p1, const void* p2) 
{ 
    const int(*x)[3] = p1; 
    const int(*y)[3] = p2; 
  
    return (*x)[2] - (*y)[2]; 
} 
  
// Initialization of parent[] and rank[] arrays 
void makeSet(int parent[], int rank[], int n) 
{ 
    for (int i = 0; i < n; i++) { 
        parent[i] = i; 
        rank[i] = 0; 
    } 
} 
  
// Function to find the parent of a node 
int findParent(int parent[], int component) 
{ 
    if (parent[component] == component) 
        return component; 
  
    return parent[component] 
           = findParent(parent, parent[component]); 
} 
  
// Function to unite two sets 
void unionSet(int u, int v, int parent[], int rank[], int n) 
{ 
    // Finding the parents 
    u = findParent(parent, u); 
    v = findParent(parent, v); 
  
    if (rank[u] < rank[v]) { 
        parent[u] = v; 
    } 
    else if (rank[u] > rank[v]) { 
        parent[v] = u; 
    } 
    else { 
        parent[v] = u; 
  
        // Since the rank increases if 
        // the ranks of two sets are same 
        rank[u]++; 
    } 
} 
  
// Function to find the MST 
void kruskalAlgo(int n, int edge[n][3]) 
{ 
    // First we sort the edge array in ascending order 
    // so that we can access minimum distances/cost 
    qsort(edge, n, sizeof(edge[0]), comparator); 
    clock_t start = clock(); 
  
    int parent[n]; 
    int rank[n]; 
  
    // Function to initialize parent[] and rank[] 
    makeSet(parent, rank, n); 
  
    // Array to store the edges in the MST
    int mstEdges[n][3];
    int mstEdgeCount = 0;
    int mstWeight = 0;

    for (int i = 0; i < n; i++) { 
        int u = edge[i][0];
        int v = edge[i][1];
        int wt = edge[i][2];

        int v1 = findParent(parent, u); 
        int v2 = findParent(parent, v); 
  
        // If the parents are different, union the sets and add the edge to MST
        if (v1 != v2) { 
            unionSet(v1, v2, parent, rank, n);
            mstEdges[mstEdgeCount][0] = u;
            mstEdges[mstEdgeCount][1] = v;
            mstEdges[mstEdgeCount][2] = wt;
            mstEdgeCount++;
            mstWeight += wt;
        } 
    } 
    clock_t end = clock();
    printf("Time for calc: %ld microseconds\n", end - start); 

    // Print the edges and total weight of the MST after timing ends
    printf("Edge \tWeight\n");
    for (int i = 0; i < mstEdgeCount; i++) {
        printf("%d - %d \t%d\n", mstEdges[i][0], mstEdges[i][1], mstEdges[i][2]);
    }
    printf("Total weight of MST: %d\n", mstWeight);
} 
  
// Driver code 
int main() 
{ 
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
  
    kruskalAlgo(21, info2); 
  
    return 0; 
}