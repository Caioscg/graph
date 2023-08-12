#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 1000

struct Graph {
    int num_nodes;
    int adjacency_matrix[MAX_NODES][MAX_NODES];
    char* name[MAX_NODES];
    char* state[MAX_NODES][100];    // estados do spam
};

int visited[MAX_NODES][100];
int conexoes[MAX_NODES][100] = {0};

struct Graph* createGraph(int num_nodes) {  // cria grafo
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->num_nodes = num_nodes;

    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            graph->adjacency_matrix[i][j] = 0;  // sem conexoes
        }
    }

    return graph;
}

void addEdge(struct Graph* graph, int node1, int node2) {
    graph->adjacency_matrix[node1][node2] = 1;  // cria as conexoes
}

void dfs(struct Graph* graph, int node, int numNodes, int contador) {
    visited[node][contador] = 1; // Marcar o nó como visitado
    conexoes[node][contador] = 0; //quantidade de conexoes de determinado no


    for (int i = 1; i <= numNodes; i++) {
        if (graph->adjacency_matrix[node][i]) {
            conexoes[node][contador]++;     //  adiciona uma conexão

            if(!visited[i][contador]) {
                dfs(graph, i, numNodes, contador); // Recursivamente visitar os nós vizinhos não visitados
            }
        }
    }
}

int main () {

    while(1) {

        int nPessoas;

        scanf("%d", &nPessoas);
        if (nPessoas == 0) return 0;

        struct Graph* graph = createGraph(nPessoas);    //cria grafo

        for (int i = 1; i <= nPessoas; i++) {
            int conexao;

            while(1) {
                scanf("%d", &conexao);
                if (conexao == 0) break;
                else {
                    addEdge(graph, i, conexao); // cria as arestas
                }
            }
        }
        
        int contador = 0;
        int startNode, T1[100], T2[100];
        char adj1[100][21], adj2[100][21], adj3[100][21];

            while (1) {
                contador++;

                scanf("%d", &startNode);

                if (startNode == 0) break;

                scanf("%d %d %s %s %s", &T1[contador], &T2[contador], &adj1[contador], &adj2[contador], &adj3[contador]);

                for (int i = 1; i <= nPessoas; i++) {   // reset do visited e conexoes
                    visited[i][contador] = 0;
                    conexoes[i][contador] = 0;
                }

                dfs(graph, startNode, nPessoas, contador);  // percorre o grafo contando as conexões de cada nó
            }

            for (int i = 1; i <= nPessoas; i++) {
                for (int j = 1; j < contador; j++) {

                    if (conexoes[i][j] < T1[j]) {       // diferentes estados
                        graph->state[i][j] = adj1[j];         

                    } 

                    else if (conexoes[i][j] >= T2[j]) {
                        graph->state[i][j] = adj3[j];
                        
                    }
                    else {
                        graph->state[i][j] = adj2[j];
                    }
                }
            }
            

        for (int i = 1; i <= nPessoas; i++) {
            graph->name[i] = (char *)malloc(21 * sizeof(char)); // Alocar memória para o nome

            char name[21];
            scanf("%s", name);

            strcpy(graph->name[i], name); // Copiar o nome para a alocação de memória
        }

        for (int i = 1; i <= nPessoas; i++) {
            printf("%s: ", graph->name[i]);
            for (int j = 1; j < contador; j++) {
                printf("%s ",  graph->state[i][j]);
            }
            printf("\n");
        }
    }

    return 0;
}