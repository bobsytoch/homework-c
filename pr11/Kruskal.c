#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Структура для представлення ребра графа
struct Edge {
    int start, end, weight;
};

// Структура для представлення графа
struct Graph {
    int V, E; // Кількість вершин і ребер
    struct Edge* edges; // Масив ребер
};

// Структура для представлення підмножини (для алгоритму об'єднання)
struct Subset {
    int parent;
    int rank;
};

// Функція для створення графа
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edges = (struct Edge*) malloc(E * sizeof(struct Edge));
    return graph;
}

// Функція для знаходження підмножини, до якої належить елемент i
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent); // Шляхова компресія
    }
    return subsets[i].parent;
}

// Функція для об'єднання двох підмножин
void unionSubsets(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    // Приєднуємо дерево меншого рангу до дерева більшого рангу
    if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
    } else if (subsets[xroot].rank > subsets[yroot].rank) {
        subsets[yroot].parent = xroot;
    } else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Функція для сортування ребер за вагою
int compareEdges(const void* a, const void* b) {
    struct Edge* edgeA = (struct Edge*)a;
    struct Edge* edgeB = (struct Edge*)b;
    return edgeA->weight - edgeB->weight;
}

// Функція реалізації алгоритму Крускала
void kruskalMST(struct Graph* graph) {
    int V = graph->V;
    struct Edge result[V]; // Масив для зберігання MST
    int e = 0; // Поточний індекс результатного масиву
    int i = 0; // Поточний індекс для ітерації ребер

    // Сортуємо всі ребра за вагою
    qsort(graph->edges, graph->E, sizeof(graph->edges[0]), compareEdges);

    // Створюємо підмножини для кожної вершини
    struct Subset* subsets = (struct Subset*) malloc(V * sizeof(struct Subset));
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Проходимо по ребрах і додаємо їх у MST
    while (e < V - 1 && i < graph->E) {
        struct Edge nextEdge = graph->edges[i++];
        int x = find(subsets, nextEdge.start);
        int y = find(subsets, nextEdge.end);

        // Якщо додавання ребра не створює цикл, додаємо його до MST
        if (x != y) {
            result[e++] = nextEdge;
            unionSubsets(subsets, x, y);
        }
    }

    // Виведення MST
    printf("Ребро \tВага\n");
    for (i = 0; i < e; i++) {
        printf("%d - %d \t%d\n", result[i].start + 1, result[i].end + 1, result[i].weight);
    }

    free(subsets);
}

int main() {
    int V, E;

    printf("Введіть кількість вершин: ");
    scanf("%d", &V);
    printf("Введіть кількість ребер: ");
    scanf("%d", &E);

    struct Graph* graph = createGraph(V, E);

    printf("Введіть ребра у форматі (початок кінець вага):\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &graph->edges[i].start, &graph->edges[i].end, &graph->edges[i].weight);
        graph->edges[i].start--; // Перетворення до індексації з 0
        graph->edges[i].end--;
    }

    clock_t start = clock();

    kruskalMST(graph);

    clock_t end = clock();

    double time_taken = ((double)(end - start) / CLOCKS_PER_SEC) * 1e6;
    printf("Час виконання алгоритму Крускала: %.0f мкс\n", time_taken);

    free(graph->edges);
    free(graph);
    return 0;
}
