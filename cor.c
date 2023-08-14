#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 1026

struct Graph {
    int cor[MAX_NODES][MAX_NODES];  // 0 preto, 1 branco
    int numero[MAX_NODES*2];
};

int visited[MAX_NODES*2] = {0};

struct Graph* createGraph(int I, int J) {  // cria grafo
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    int number = 0;

    for (int i = 0; i <= I+1; i++) {
        for (int j = 0; j <= J+1; j++) {
            graph->cor[i][j] = 0;
            graph->numero[number] = number;
            number++;
        }
    }

    return graph;
}

void dfs(struct Graph* graph, int i, int j, int M, int node) {
    visited[node] = 1; // Marcar o nó como visitado

    if (graph->cor[i][j-1] == 1 && !visited[node-1]) {
        dfs(graph, i, j-1, M, node-1);
    }

    if (graph->cor[i][j+1] == 1 && !visited[node+1]) {
        dfs(graph, i, j+1, M, node+1);
    }

    if (graph->cor[i+1][j] == 1 && !visited[node+M+2]) {
        dfs(graph, i+1, j, M, node+M+2);
    }

    if (graph->cor[i-1][j] == 1 && !visited[node-M-2]) {
        dfs(graph, i-1, j, M, node-M-2);
    }

}

int main () {

    int N, M;
    char cor[MAX_NODES];

    scanf("%d %d", &N, &M);
    struct Graph* graph = createGraph(N+2, M+2); 
    int number = 0;
    
    for (int i = 1; i <= N; i++) {
        scanf("%s", cor);
        for (int j = 1; j <= M; j++) {
            if (cor[j-1] == '.') {
                graph->cor[i][j] = 1;
            }
        }
    }
    
    int quantidade = 0;
    for (int i = 0; i <= N+1; i++) {
        for (int j = 0; j <= M+1; j++) {
            if (graph->cor[i][j] == 1 && !visited[number]) {
                dfs(graph, i, j, M, number);
                quantidade++;
            }
            number++;
        }
    }

    printf("%d\n", quantidade);

    return 0;
}