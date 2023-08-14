#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 1024

struct Graph {
    int num_nodes;
    int adjacency_matrix[MAX_NODES*2][MAX_NODES*2];
    int cor[MAX_NODES];  // 1 preto, 0 branco
    int numero[MAX_NODES*2];
    int quantidade;
};

int visited[MAX_NODES*2];

struct Graph* createGraph(int num_nodes) {  // cria grafo
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->num_nodes = num_nodes;
    int number = 0;

    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            graph->adjacency_matrix[i][j] = 0;  // sem conexoes
            graph->cor[i][j] = 0;
            graph->numero[number] = number;
            number++;
        }
    }

    return graph;
}

void addEdge(struct Graph* graph, int node1, int node2) {
    graph->adjacency_matrix[node1][node2] = 1;  // cria as conexoes
    graph->adjacency_matrix[node2][node1] = 1;
}

void dfs(struct Graph* graph, int node, int M) {
    if (visited[node] == 1) return;

    visited[node] = 1; // Marcar o nó como visitado

    if (graph->adjacency_matrix[node][node-1] && !visited[node-1]) dfs(graph, node-1, M);

    if (graph->adjacency_matrix[node][node+1] && !visited[node+1]) dfs(graph, node+1, M);

    if (graph->adjacency_matrix[node][node+M] && !visited[node+M])  dfs(graph, node+M, M);
    
    graph->quantidade++;
}

void dfs2(struct Graph* graph, int node, int M) {
    visited[node] = 1; // Marcar o nó como visitado

    if (graph->adjacency_matrix[node][node-1] && !visited[node-1]) dfs2(graph, node-1, M);

    if (graph->adjacency_matrix[node][node+1] && !visited[node+1]) dfs2(graph, node+1, M);

    if (graph->adjacency_matrix[node][node+M] && !visited[node+M])  dfs2(graph, node+M, M);
}

void addColor(struct Graph* graph, int node, char *cor) {
    if (cor[0] == 'o') graph->cor[node] = 1;
    else graph->cor[node] = 0;
}

int main () {

    int N, M;
    char cor[1];

    scanf("%d %d", &N, &M);
    struct Graph* graph = createGraph(N*M); 

    for (int i = 0; i < N; i++) {

        scanf("%s", cor);
        addColor(graph, i, cor);

        if (cor == ".") {
            if (graph->cor[i-1][j] == '.') addEdge(graph, i, number-M);
            if (graph->cor[i][j-1] == '.') addEdge(graph, i, number-1);
        }

    }

    graph->quantidade = 0;
    for (int i = 0; i < N*M; i++) {
        dfs(graph, i, M);
    }

    printf("%d\n", graph->quantidade);

    return 0;
}