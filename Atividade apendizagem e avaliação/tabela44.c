#include <stdio.h>
#include <limits.h>

int main() {
    int N = 4;  
    int cost[4][4] = {
        {0, 1, 4, INT_MAX}, 
        {1, 0, 2, 6},        
        {4, 2, 0, 3},        
        {INT_MAX, 6, 3, 0}   
    };

    struct Node {
        int dist[4];  
    };

    struct Node nodes[4];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                nodes[i].dist[j] = 0;
            } else {
                nodes[i].dist[j] = cost[i][j];
            }
        }
    }

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

    return 0;
}
