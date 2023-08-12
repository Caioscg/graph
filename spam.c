#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 1000

struct Node {
    int value;
    int name;
    struct Node* next;
};

struct Graph {
    int num_nodes;
    struct Node** adjacency_list;
};

struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->next = NULL;
    newNode->name =  NULL;
    return newNode;
}

struct Graph* createGraph(int num_nodes) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->num_nodes = num_nodes;
    graph->adjacency_list = (struct Node**)malloc(num_nodes * sizeof(struct Node*));

    for (int i = 0; i < num_nodes; i++) {
        graph->adjacency_list[i] = NULL;
    }

    return graph;
}

void addEdge(struct Graph* graph, int node1, int node2) {
    struct Node* newNode = createNode(node2);
    newNode->next = graph->adjacency_list[node1];
    graph->adjacency_list[node1] = newNode;

    //newNode = createNode(node1);
    //newNode->next = graph->adjacency_list[node2];
    //graph->adjacency_list[node2] = newNode;
}


int main () {

    int nPessoas;

    scanf("%d", &nPessoas);
    if (nPessoas == 0) return 0;

    struct Graph* graph = createGraph(nPessoas);

    for (int i = 1; i <= nPessoas; i++) {
        int conexao;

        while(1) {
            scanf("%d", &conexao);
            if (conexao == 0) break;
            else {
                addEdge(graph, i, conexao);
            }
        }
    }



    return 0;
}