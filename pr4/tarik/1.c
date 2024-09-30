#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void fillBranch(int arr[], int *visited, int size, int index, Node* current) {
    if (current == NULL || !(current->data)) return;

    if (index + arr[index] < size && !visited[index + arr[index]]) {
        visited[index] = 1;
        current->right = createNode(arr[index + arr[index]]);
        fillBranch(arr, visited, size, index + arr[index], current->right);
        visited[index] = 0;
    }

    if (index - arr[index] >= 0 && !visited[index - arr[index]]) {
        visited[index] = 1;
        current->left = createNode(arr[index - arr[index]]);
        fillBranch(arr, visited, size, index - arr[index], current->left);
    }

}

void printPathsRecursive(Node* root, char path[], int pathLen, int dir) {
    if (root == NULL) return;

    if (dir == 0) path[pathLen++] = 'L';
    else if (dir == 1) path[pathLen++] = 'R';
    path[pathLen++] = root->data + '0';

    if (root->data == 0) {
        path[pathLen++] = '\0';
        printf("%s\n", path);
    } else {
        printPathsRecursive(root->left, path, pathLen, 0);
        printPathsRecursive(root->right, path, pathLen, 1);
    }
}

int main() {
    int arr[10];
    int visited[10] = { 1 };
    srand(time(NULL));

    for (int i = 0; i < 9; i++) 
        arr[i] = rand() % 9 + 1;
    arr[9] = 0;

    printf("Generated array: ");
    for (int i = 0; i < 10; i++) 
        printf("%d ", arr[i]);
        printf("\n");

    Node* root = createNode(arr[0]);
    fillBranch(arr, visited, 10, 0, root);

    char path[19];
    printPathsRecursive(root, path, 0, -1);

    return 0;
}