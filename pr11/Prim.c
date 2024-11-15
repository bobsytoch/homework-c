#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>

#define INF 9999999

// Функція для знаходження індексу мінімального елемента в масиві key, який ще не включений в MST
int minKey(int key[], bool selected[], int V) {
    int min = INF, min_index;

    for (int v = 1; v <= V; v++) {  // починаємо з 1
        if (!selected[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

// Функція для виведення MST, представленого масивом parent[]
void printMST(int parent[], int graph[][101], int V) {
    printf("Ребро \tВага\n");
    for (int i = 2; i <= V; i++) {
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
    }
}

// Основна функція для реалізації алгоритму Прима з використанням масиву як черги з пріоритетом
void primMST(int graph[][101], int V) {
    int parent[V + 1];   // Масив для зберігання побудованого MST
    int key[V + 1];      // Масив для відстеження мінімальної ваги для кожної вершини
    bool selected[V + 1]; // Масив для відстеження включення вершини в MST

    // Ініціалізація ключів як нескінченних і selected[] як false
    for (int i = 1; i <= V; i++) {
        key[i] = INF;
        selected[i] = false;
    }

    // Починаємо з першої вершини
    key[1] = 0;
    parent[1] = -1; // Перший вузол завжди корінь MST

    for (int count = 1; count < V; count++) {
        int u = minKey(key, selected, V); // Обираємо вершину з мінімальною вагою
        selected[u] = true; // Включаємо обрану вершину в MST

        // Оновлюємо ваги суміжних вершин, які ще не включені в MST
        for (int v = 1; v <= V; v++) {
            if (graph[u][v] && !selected[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Виводимо побудоване MST
    printMST(parent, graph, V);
}

int main() {
    int V, E;
    
    printf("Введіть кількість вершин: ");
    scanf("%d", &V);

    int graph[101][101];
    
    // Ініціалізуємо матрицю суміжності нулями
    for (int i = 1; i <= V; i++) {
        for (int j = 1; j <= V; j++) {
            graph[i][j] = 0;
        }
    }

    printf("Введіть кількість ребер: ");
    scanf("%d", &E);

    printf("Введіть ребра у форматі (початок кінець вага):\n");
    for (int i = 0; i < E; i++) {
        int u, v, weight;
        scanf("%d %d %d", &u, &v, &weight);
        graph[u][v] = weight;
        graph[v][u] = weight; // Для неорієнтованого графу
    }

    printf("\n");
    
     clock_t start = clock();

    primMST(graph, V);

    clock_t end = clock();

    double time_taken = ((double)(end - start) / CLOCKS_PER_SEC) * 1e6;
    printf("\nЧас виконання алгоритму Прима: %.0f мкс\n", time_taken);

    return 0;
}
