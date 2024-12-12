#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

const int MAX_NOS = 100;

int grafo[100][100];
int num_nos;         

void inicializarGrafo(int n) {
    num_nos = n;
    for (int i = 0; i < MAX_NOS; i++) {
        for (int j = 0; j < MAX_NOS; j++) {
            grafo[i][j] = (i == j) ? 0 : INT_MAX; 
        }
    }
}

void adicionarNo() {
    num_nos++;
    for (int i = 0; i < num_nos; i++) {
        grafo[i][num_nos - 1] = INT_MAX; 
        grafo[num_nos - 1][i] = INT_MAX;
    }
    printf("Nó %d adicionado à rede.\n", num_nos - 1);
}

void removerNo(int no) {
    if (no >= num_nos) {
        printf("Nó inválido.\n");
        return;
    }
    for (int i = 0; i < num_nos; i++) {
        grafo[no][i] = INT_MAX;
        grafo[i][no] = INT_MAX;
    }
    printf("Nó %d removido da rede.\n", no);
}

void dijkstra(int origem) {
    int distancia[100], visitado[100];
    int caminho[100];
    
    for (int i = 0; i < num_nos; i++) {
        distancia[i] = INT_MAX;
        visitado[i] = 0;
        caminho[i] = -1;
    }

    distancia[origem] = 0;

    for (int i = 0; i < num_nos - 1; i++) {
        int minDist = INT_MAX, noAtual = -1;

        for (int j = 0; j < num_nos; j++) {
            if (!visitado[j] && distancia[j] < minDist) {
                minDist = distancia[j];
                noAtual = j;
            }
        }

        if (noAtual == -1) break;

        visitado[noAtual] = 1;

        for (int j = 0; j < num_nos; j++) {
            if (!visitado[j] && grafo[noAtual][j] != INT_MAX &&
                distancia[noAtual] + grafo[noAtual][j] < distancia[j]) {
                distancia[j] = distancia[noAtual] + grafo[noAtual][j];
                caminho[j] = noAtual;
            }
        }
    }

    printf("Tabela de Roteamento (Origem: %d):\n", origem);
    printf("Nó Destino | Distância | Caminho\n");
    for (int i = 0; i < num_nos; i++) {
        if (distancia[i] == INT_MAX) {
            printf("     %d     |   INFINITO   |    -\n", i);
        } else {
            printf("     %d     |     %d       |    %d\n", i, distancia[i], caminho[i]);
        }
    }
}

int main() {
    int n, opcao, origem, no1, no2, peso;

    printf("Digite o número inicial de nós na rede: ");
    scanf("%d", &n);
    inicializarGrafo(n);

    while (1) {
        printf("\nOpções:\n");
        printf("1. Adicionar uma aresta\n");
        printf("2. Remover uma aresta\n");
        printf("3. Adicionar um nó\n");
        printf("4. Remover um nó\n");
        printf("5. Executar Dijkstra\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            printf("Digite os nós e o peso da aresta (no1 no2 peso): ");
            scanf("%d %d %d", &no1, &no2, &peso);
            if (no1 < num_nos && no2 < num_nos) {
                grafo[no1][no2] = peso;
                grafo[no2][no1] = peso; // Rede não direcionada
                printf("Aresta adicionada entre %d e %d com peso %d.\n", no1, no2, peso);
            } else {
                printf("Nó(s) inválido(s).\n");
            }
            break;

        case 2:
            printf("Digite os nós da aresta a remover (no1 no2): ");
            scanf("%d %d", &no1, &no2);
            if (no1 < num_nos && no2 < num_nos) {
                grafo[no1][no2] = INT_MAX;
                grafo[no2][no1] = INT_MAX;
                printf("Aresta entre %d e %d removida.\n", no1, no2);
            } else {
                printf("Nó(s) inválido(s).\n");
            }
            break;

        case 3:
            adicionarNo();
            break;

        case 4:
            printf("Digite o nó a remover: ");
            scanf("%d", &no1);
            removerNo(no1);
            break;

        case 5:
            printf("Digite o nó de origem para executar o Dijkstra: ");
            scanf("%d", &origem);
            if (origem < num_nos) {
                dijkstra(origem);
            } else {
                printf("Nó inválido.\n");
            }
            break;

        case 6:
            exit(0);

        default:
            printf("Opção inválida.\n");
        }
    }

    return 0;
}
