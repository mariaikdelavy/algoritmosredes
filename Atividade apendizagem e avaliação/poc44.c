#include <stdio.h>
#include <limits.h>

int cost[10][10];  
int N = 4;  

struct Node {
    int dist[10];  
};

struct Node nodes[10];  

void initializeGraph() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                cost[i][j] = 0;
                nodes[i].dist[j] = 0;
            } else {
                cost[i][j] = (cost[i][j] == 0) ? INT_MAX : cost[i][j];  
                nodes[i].dist[j] = cost[i][j];
            }
        }
    }
}

void addNode(int newCost[10][10], int newN) {
    N = newN;  
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cost[i][j] = newCost[i][j];  
            nodes[i].dist[j] = cost[i][j];  
        }
    }
    initializeGraph();  
}

void removeNode(int nodeToRemove) {
    if (nodeToRemove < 0 || nodeToRemove >= N) {
        printf("Nó inválido para remoção!\n");
        return;
    }
    for (int i = nodeToRemove; i < N - 1; i++) {
        for (int j = 0; j < N; j++) {
            cost[i][j] = cost[i + 1][j];
            nodes[i].dist[j] = nodes[i + 1].dist[j];
        }
    }
    N--;  
    initializeGraph();  
}

void updateDistances() {
    int updated;
    do {
        updated = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {
                    if (nodes[i].dist[j] > nodes[i].dist[k] + cost[k][j]) {
                        nodes[i].dist[j] = nodes[i].dist[k] + cost[k][j];
                        updated = 1;
                    }
                }
            }
        }
    } while (updated);
}

void printDistances() {
    for (int i = 0; i < N; i++) {
        printf("Distâncias do nó %d: ", i);
        for (int j = 0; j < N; j++) {
            if (nodes[i].dist[j] == INT_MAX) {
                printf("INF ");
            } else {
                printf("%d ", nodes[i].dist[j]);
            }
        }
        printf("\n");
    }
}

int main() {
    int initialCost[4][4] = {
        {0, 1, 4, INT_MAX},  
        {1, 0, 2, 6},        
        {4, 2, 0, 3},        
        {INT_MAX, 6, 3, 0}   
    };
    
    addNode(initialCost, 4);
    printf("Grafo Inicial:\n");
    printDistances();  
    
    int newCost[5][5] = {
        {0, 1, 4, INT_MAX, INT_MAX},
        {1, 0, 2, 6, INT_MAX},
        {4, 2, 0, 3, INT_MAX},
        {INT_MAX, 6, 3, 0, 2},
        {INT_MAX, INT_MAX, INT_MAX, 2, 0}
    };
    
    addNode(newCost, 5);  
    printf("\nApós adicionar o nó 4:\n");
    printDistances();  
    
    removeNode(2);
    printf("\nApós remover o nó 2:\n");
    printDistances();  
    
    return 0;
}
